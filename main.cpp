#define CPPHTTPLIB_OPENSSL_SUPPORT 1

#include <iostream>
#include <memory>
#include "spdlog/spdlog.h"
#include "json/json.h"
#include "httplib/httplib.h"
#include "SimpleIni.h"

int main() {

    httplib::Client cli("https://api.xygeng.cn");
    cli.set_follow_location(true);
    httplib::Headers headers = {
            {"User-Agent",      "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
                                "(KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36 Edg/125.0.0.0"},
            {"Accept-Encoding", "gzip, deflate"},
            {"Accept-Charset",  "utf-8"}
    };
    auto res = cli.Get("/one", headers);
    spdlog::info(res->status);
    spdlog::info(res->body);

//    const std::string rawJson = R"({"Age": 20, "Name": "colin"})";
    const std::string rawJson = res->body;
    Json::Value root;
    Json::Reader reader;
    reader.parse(rawJson, root);
    const Json::Value &data = root["data"];
    const auto id = data["id"].asString();
    const std::string name = data["name"].asString();
    const std::string tag = data["tag"].asString();
    const std::string origin = data["origin"].asString();
    const std::string content = data["content"].asString();
    const std::string created_at = data["created_at"].asString();

    spdlog::info("id:{},name:{},tag:{},origin:{},content:{},created_at:{}", id, name, tag, origin, content,
                 created_at);

    // 定义ini文档对象
    CSimpleIniA ini;

// 加载ini文件
    std::string settingFilePath = "./setting.ini";
    SI_Error rc;
    rc = ini.LoadFile(settingFilePath.c_str());    // 另一种方式：SI_Error LoadFile(FILE * a_fpFile);
    if (rc < 0) {
        spdlog::info("加载 {} ini 文件失败！\n", settingFilePath);
        return -1;
    }

    std::string setName = ini.GetValue("server", "name", "");
    spdlog::info("ini name:{}", setName);

    std::string newName = "测试修改";
    ini.SetValue("server", "name", (newName + setName).c_str());

    ini.SaveFile(settingFilePath.c_str());

    //std::cin.get();

    // 无限轮询 读取不停追加的日志文本
    std::ifstream ifs("test.log");
    if (ifs.is_open()) {
        std::string line;
        while (true) {
            while (std::getline(ifs, line))
                spdlog::info(line);
            if (!ifs.eof()) break;
            ifs.clear();

            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }


    return 0;
}
