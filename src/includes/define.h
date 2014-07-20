#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include <stdlib.h>
#include <libgen.h>
#include <unistd.h>
#include <iostream>
#include <string>

const char* CURRENT_BOOST_VERSION = "1_55_0";
const char* STANDARD_BOOST_VERSION = "1.55.0";

std::string GetCurrentPath()
{
    char buff[1024];
    int len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
    if (len != -1) {
      buff[len] = '\0';

      std::string path = buff;
      size_t last_slash = path.rfind("/");
      path = path.substr(0, last_slash);

      return path;
    }

    return "";
}

void DownloadBoostFromInternet()
{
    char buff[2048];

    sprintf(
        buff,
        "wget http://softlayer-dal.dl.sourceforge.net/project/boost/boost/%s/boost_%s.tar.bz2 --output-document=boost.tar.bz2",
        STANDARD_BOOST_VERSION,
        CURRENT_BOOST_VERSION
    );

    system(buff);
}

void UnzipBoostArchive()
{
    system("tar -xjvf boost.tar.bz2");
}

void BootstrapBoost()
{
    char buff[2048];
    sprintf(
        buff,
        "cd %s/boost_%s && %s\"%s\"",
        GetCurrentPath().c_str(),
        CURRENT_BOOST_VERSION,
        "./bootstrap.sh --prefix=",
        GetCurrentPath().c_str()
    );

    system(buff);
}

void BuildBoost()
{
    char buff[2048];
    sprintf(
        buff,
        "cd %s/boost_%s && %s",
        GetCurrentPath().c_str(),
        CURRENT_BOOST_VERSION,
        "./b2 install"
    );

    system(buff);
}

void ExtractLibraries()
{
    char buff[2048];
    sprintf(
        buff,
        "cd %s && mkdir lib && %s",
        GetCurrentPath().c_str(),
        "find . -type f -iname '*.o' -exec cp -t'./lib/' {} \\+"
    );

    system(buff);
}

void CopyHeaders()
{
    char buff[2048];
    sprintf(
        buff,
        "cd %s && cp -r boost_%s/boost %s/",
        GetCurrentPath().c_str(),
        CURRENT_BOOST_VERSION,
        GetCurrentPath().c_str()
    );

    system(buff);
}

void CopyDocumentation()
{
    char buff[2048];
    sprintf(
        buff,
        "cd %s && cp -r boost_%s/doc %s/doc",
        GetCurrentPath().c_str(),
        CURRENT_BOOST_VERSION,
        GetCurrentPath().c_str()
    );

    system(buff);
}

void InstallBoost()
{
    DownloadBoostFromInternet();
    UnzipBoostArchive();
    BootstrapBoost();
    BuildBoost();
    ExtractLibraries();
    CopyHeaders();
    CopyDocumentation();
}

#endif // DEFINE_H_INCLUDED
