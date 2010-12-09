#include "HotValue.hpp"

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <string.h>

struct HotValue
{
   enum Type
   {
      INT,
      FLOAT
   };
   
   Type type;
   
   union
   {
      int i;
      float f;
   } value;
};

typedef std::map<std::pair<unsigned int, unsigned int>, HotValue*> HotValueMap;

struct File
{
   time_t lastModified;
   HotValueMap hotValues;
};

typedef std::map<std::string, File*> FileMap;

static FileMap g_hotValues;

inline time_t getFileModifiedTime(std::string const& filename)
{	
	struct stat statInfo;
	stat(filename.c_str(), &statInfo);
	return statInfo.st_mtime;
}

HotValue * lookupHotValue(std::string const& filename, unsigned int line, unsigned int count)
{
   FileMap::iterator fileIt = g_hotValues.find(filename);
   if (fileIt != g_hotValues.end())
   {
      File * file = fileIt->second;
      HotValueMap::iterator hotValueIt = file->hotValues.find(std::make_pair(line, count));
      if (hotValueIt != file->hotValues.end())
         return hotValueIt->second;
   }



   return 0;
}

HotValue * newHotValue(std::string const& filename, unsigned int line, unsigned int count, int value)
{
   HotValue * hotValue = new HotValue;
   hotValue->type = HotValue::INT;
   hotValue->value.i = value;

   FileMap::iterator fileIt = g_hotValues.find(filename);
   if (fileIt != g_hotValues.end())
   {
      File * file = fileIt->second;
      file->hotValues.insert(std::make_pair(std::make_pair(line, count), hotValue));
   }
   else
   {
      File * file = new File;
      
      file->lastModified = getFileModifiedTime(filename);
      file->hotValues.insert(std::make_pair(std::make_pair(line, count), hotValue));
      
      g_hotValues.insert(std::make_pair(filename, file));
   }
   
   return hotValue;
}

HotValue * newHotValue(std::string const& filename, unsigned int line, unsigned int count, float value)
{
   HotValue * hotValue = new HotValue;
   hotValue->type = HotValue::FLOAT;
   hotValue->value.f = value;

   FileMap::iterator fileIt = g_hotValues.find(filename);
   if (fileIt != g_hotValues.end())
   {
      File * file = fileIt->second;
      file->hotValues.insert(std::make_pair(std::make_pair(line, count), hotValue));
   }
   else
   {
      File * file = new File;
      file->lastModified = getFileModifiedTime(filename);
      file->hotValues.insert(std::make_pair(std::make_pair(line, count), hotValue));
      g_hotValues.insert(std::make_pair(filename, file));
   }
   
   return hotValue;
}

int hotValue(const char * file, unsigned int line, unsigned int count, int value)
{
   HotValue * hotValue = lookupHotValue(file, line, count);
   if (!hotValue)
      hotValue = newHotValue(file, line, count, value);
            
   return hotValue->value.i;
}

float hotValue(const char * file, unsigned int line, unsigned int count, float value)
{
   HotValue * hotValue = lookupHotValue(file, line, count);
   if (!hotValue)
      hotValue = newHotValue(file, line, count, value);
      
   return hotValue->value.f;
}

void parseFile(std::string const& filename)
{
   std::ifstream stream(filename.c_str());
   
   if (!stream)
      return;
   
   std::string line;
   unsigned int lineCount = 1;
   bool comment = false;
   
   while (std::getline(stream, line))
   {
      // Strip C++ comments
      std::string::size_type pos = line.find("//");
      if (pos != std::string::npos)
         line = line.substr(0, pos);
         
      // Stip C comments
      if (!comment)
      {
         std::string::size_type startComment = line.find("/*");
         if (startComment != std::string::npos)
         {
            std::string::size_type endComment = line.substr(startComment + 2).find("*/");
            
            if (endComment == std::string::npos)
               comment = true;
            else
               line = line.substr(0, startComment) + line.substr(startComment + endComment + 2);
         }
      }
      else
      {
         std::string::size_type endComment = line.find("*/");
         if (endComment != std::string::npos)
            line = line.substr(endComment + 2);
         else
            continue;
      }

      
      // Lets search for a H() macro
      pos = line.find("H(");
      if (pos != std::string::npos)
      {
         std::string::size_type end = line.substr(pos + 2).find(")");
         if (end != std::string::npos)
         {
            std::string value = line.substr(pos + 2, end);
            
            std::cout << filename << ":" << lineCount << " - Value: " << value << std::endl;
            
            HotValue * hotValue = lookupHotValue(filename, lineCount, 0);
            if (hotValue)
            {
               if (hotValue->type == HotValue::INT)
                  hotValue->value.i = atoi(value.c_str());
               else
                  hotValue->value.f = atof(value.c_str());

            }
         }
      }
      
      // Lets search for HC() macros on this line
      std::string currentLine = line;
      while ((pos = currentLine.find("HC(")) != std::string::npos)
      {
         std::cout << "HC() value" << std::endl;
         std::string::size_type comma = currentLine.substr(pos + 3).find(",");
         std::string::size_type end = currentLine.substr(pos + 3 + comma).find(")");
         
         if (comma != std::string::npos && end != std::string::npos)
         {         
            int count = atoi(currentLine.substr(pos + 3, comma).c_str());
            std::string value = currentLine.substr(pos + 3 + comma + 1, end - 1);
            value = value.substr(value.find_first_not_of(" "));
            
            HotValue * hotValue = lookupHotValue(filename, lineCount, count);
            if (hotValue)
            {
               if (hotValue->type == HotValue::INT)
                  hotValue->value.i = atoi(value.c_str());
               else
                  hotValue->value.f = atof(value.c_str());
            }            
         }
         
         currentLine = currentLine.substr(pos + 3 + end);
      }
         
      lineCount++;
   }
   
   stream.close();
}

void updateHotValues()
{
   for (FileMap::iterator it = g_hotValues.begin(); it != g_hotValues.end(); ++it)
   {
      File * file = it->second;
      time_t modifiedTime = getFileModifiedTime(it->first);
      if (file->lastModified < modifiedTime)
      {
         parseFile(it->first);
         file->lastModified = modifiedTime;
      }
   }
}
