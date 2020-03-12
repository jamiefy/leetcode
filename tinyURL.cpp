//
// Created by anranzhai on 2020/3/12.
//
#include <map>
std::map<int,std::string> tinyMap;
int i=0;
// Encodes a URL to a shortened URL.
std::string encode(std::string longUrl) {
    tinyMap[i]=longUrl;
    return "http://tiny.com/"+i++;
}

// Decodes a shortened URL to its original URL.
std::string decode(std::string shortUrl) {
    return tinyMap[std::atoi(shortUrl.replace(0,16,"").c_str())];//leetcode能通过atoi不能通过stoi
}