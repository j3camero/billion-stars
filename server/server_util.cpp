#include <iostream>
#include <cassert>
#include <chrono>
#include <fstream>
#include <memory>
#include <cstring>

#include <boost/filesystem.hpp>
#include <json/json.h>

#include "server_util.h"

using namespace std;
using namespace startree;

void starsInRadiusHandler(HttpServer& server,
                          shared_ptr<HttpServer::Response> response,
                          shared_ptr<HttpServer::Request> request,
                          const StarTree& tree) {
    //cout << "starsInRadius called!" << endl;
    double radius, pointX, pointY, pointZ;

    string valstring;
    for (int i = 2; i < 6; i++) {
        string pair = request->path_match[i];
        int splitPoint = pair.find("=");
        string fieldname = pair.substr(0, splitPoint);
        valstring = pair.substr(splitPoint + 1);

        if (fieldname == "radius") {
            radius = atof(valstring.c_str());
        } else if (fieldname == "pointX") {
            pointX = atof(valstring.c_str());
        } else if (fieldname == "pointY") {
            pointY = atof(valstring.c_str());
        } else if (fieldname == "pointZ") {
            pointZ = atof(valstring.c_str());
        }
    }
    /*
    cout << "radius: " << radius << endl;
    cout << "x: " << pointX << endl;
    cout << "y: " << pointY << endl;
    cout << "z: " << pointZ << endl;
    */
    
    vector<const StarTree*> searchList{&tree};
    vector<const Star*> foundStars;
    starsInRadius(Vector3d(pointX, pointY, pointZ), radius,
                  searchList, foundStars);

    //cout << "Star search complete" << endl;
    
    Json::Value root;
    for (vector<const Star*>::iterator it = foundStars.begin();
         it != foundStars.end();
         ++it) {
        const Star* pStar = *it;
        Json::Value star(Json::objectValue);
        star["sid"] = to_string(pStar->id());
        star["x"] = to_string(pStar->position().x());
        star["y"] = to_string(pStar->position().y());
        star["z"] = to_string(pStar->position().z());
        star["lum"] = to_string(pStar->lum());
        star["r"] = to_string(pStar->color()[0]);
        star["g"] = to_string(pStar->color()[1]);
        star["b"] = to_string(pStar->color()[2]);
        root.append(move(star));
    }
    //cout << "Done making JSON" << endl;

    stringstream jsonStream;
    jsonStream << root;
    *response << "HTTP/1.1 200 OK\r\n"
              << "Content-Length: " << jsonStream.str().length()
              << "\r\n\r\n" << jsonStream.str();
}

void visibleStarsHandler(HttpServer& server,
                         shared_ptr<HttpServer::Response> response,
                         shared_ptr<HttpServer::Request> request,
                         const StarTree& tree) {
    //cout << "visibleStars called!" << endl;
    double lum, pointX, pointY, pointZ;

    string valstring;
    for (int i = 2; i < 6; i++) {
        string pair = request->path_match[i];
        int splitPoint = pair.find("=");
        string fieldname = pair.substr(0, splitPoint);
        valstring = pair.substr(splitPoint + 1);

        if (fieldname == "minLum") {
            lum = atof(valstring.c_str());
        } else if (fieldname == "pointX") {
            pointX = atof(valstring.c_str());
        } else if (fieldname == "pointY") {
            pointY = atof(valstring.c_str());
        } else if (fieldname == "pointZ") {
            pointZ = atof(valstring.c_str());
        }
    }
    /*
    cout << "lum: " << lum << endl;
    cout << "x: " << pointX << endl;
    cout << "y: " << pointY << endl;
    cout << "z: " << pointZ << endl;
    */
    
    vector<const StarTree*> searchList{&tree};
    vector<const Star*> foundStars;
    visibleStars(Vector3d(pointX, pointY, pointZ), lum,
                 searchList, foundStars);

    //cout << "Star search complete" << endl;
    
    Json::Value root;
    for (vector<const Star*>::iterator it = foundStars.begin();
         it != foundStars.end();
         ++it) {
        const Star* pStar = *it;
        Json::Value star(Json::objectValue);
        star["sid"] = to_string(pStar->id());
        star["x"] = to_string(pStar->position().x());
        star["y"] = to_string(pStar->position().y());
        star["z"] = to_string(pStar->position().z());
        star["lum"] = to_string(pStar->lum());
        star["r"] = to_string(pStar->color()[0]);
        star["g"] = to_string(pStar->color()[1]);
        star["b"] = to_string(pStar->color()[2]);
        root.append(move(star));
    }
    //cout << "Done making JSON" << endl;

    stringstream jsonStream;
    jsonStream << root;
    *response << "HTTP/1.1 200 OK\r\n"
              << "Content-Length: " << jsonStream.str().length()
              << "\r\n\r\n" << jsonStream.str();
}

void visibleStarsMagicHandler(HttpServer& server,
                              shared_ptr<HttpServer::Response> response,
                              shared_ptr<HttpServer::Request> request,
                              const StarTree& tree) {
    //cout << "visibleStarsMagic called!" << endl;
    double lum, blurRad, pointX, pointY, pointZ;

    string valstring;
    for (int i = 2; i < 7; i++) {
        string pair = request->path_match[i];
        int splitPoint = pair.find("=");
        string fieldname = pair.substr(0, splitPoint);
        valstring = pair.substr(splitPoint + 1);

        if (fieldname == "minLum") {
            lum = atof(valstring.c_str());
        } else if (fieldname == "blurRad") {
            blurRad = atof(valstring.c_str());
        } else if (fieldname == "pointX") {
            pointX = atof(valstring.c_str());
        } else if (fieldname == "pointY") {
            pointY = atof(valstring.c_str());
        } else if (fieldname == "pointZ") {
            pointZ = atof(valstring.c_str());
        }
    }
    /*
    cout << "lum: " << lum << endl;
    cout << "blurRad: " << blurRad << endl;
    cout << "x: " << pointX << endl;
    cout << "y: " << pointY << endl;
    cout << "z: " << pointZ << endl;
    */
    
    vector<const StarTree*> searchList{&tree};
    vector<const Star*> foundStars;
    visibleStarsMagic(Vector3d(pointX, pointY, pointZ), lum, blurRad,
                      searchList, foundStars);

    //cout << "Star search complete" << endl;
    
    Json::Value root;
    for (vector<const Star*>::iterator it = foundStars.begin();
         it != foundStars.end();
         ++it) {
        const Star* pStar = *it;
        Json::Value star(Json::objectValue);
        star["sid"] = to_string(pStar->id());
        star["x"] = to_string(pStar->position().x());
        star["y"] = to_string(pStar->position().y());
        star["z"] = to_string(pStar->position().z());
        star["lum"] = to_string(pStar->lum());
        star["r"] = to_string(static_cast<int>(pStar->color()[0]));
        star["g"] = to_string(static_cast<int>(pStar->color()[1]));
        star["b"] = to_string(static_cast<int>(pStar->color()[2]));
        root.append(move(star));
    }
    //cout << "Done making JSON" << endl;

    stringstream jsonStream;
    jsonStream << root;
    *response << "HTTP/1.1 200 OK\r\n"
              << "Content-Length: " << jsonStream.str().length()
              << "\r\n\r\n" << jsonStream.str();
}

void visibleOctantsHandler(HttpServer& server,
                           shared_ptr<HttpServer::Response> response,
                           shared_ptr<HttpServer::Request> request,
                           const StarTree& tree) {
    //cout << "visibleOctants called!" << endl;
    double lum, pointX, pointY, pointZ;

    string valstring;
    for (int i = 2; i < 7; i++) {
        string pair = request->path_match[i];
        int splitPoint = pair.find("=");
        string fieldname = pair.substr(0, splitPoint);
        valstring = pair.substr(splitPoint + 1);

        if (fieldname == "minLum") {
            lum = atof(valstring.c_str());
        } else if (fieldname == "pointX") {
            pointX = atof(valstring.c_str());
        } else if (fieldname == "pointY") {
            pointY = atof(valstring.c_str());
        } else if (fieldname == "pointZ") {
            pointZ = atof(valstring.c_str());
        }
    }
    /*
    cout << "lum: " << lum << endl;
    cout << "x: " << pointX << endl;
    cout << "y: " << pointY << endl;
    cout << "z: " << pointZ << endl;
    */
    
    vector<const StarTree*> searchList{&tree};
    vector<uint64_t> foundNodes;

    visibleOctants(Vector3d(pointX, pointY, pointZ),
                   lum, searchList, foundNodes);

    //cout << "Star search complete" << endl;
    
    Json::Value root;
    for (vector<uint64_t>::iterator it = foundNodes.begin();
         it != foundNodes.end();
         ++it) {
        root.append(Json::Value(static_cast<Json::Value::UInt64>(*it)));
    }
    //cout << "Done making JSON" << endl;
    //cout << "----------" << endl;

    stringstream jsonStream;
    jsonStream << root;
    *response << "HTTP/1.1 200 OK\r\n"
              << "Content-Length: " << jsonStream.str().length()
              << "\r\n\r\n" << jsonStream.str();
}

void visibleOctantsMagicHandler(HttpServer& server,
                                shared_ptr<HttpServer::Response> response,
                                shared_ptr<HttpServer::Request> request,
                                const StarTree& tree) {
    //cout << "visibleOctantsMagic called!" << endl;
    double lum, blurRad, pointX, pointY, pointZ;

    string valstring;
    for (int i = 2; i < 7; i++) {
        string pair = request->path_match[i];
        int splitPoint = pair.find("=");
        string fieldname = pair.substr(0, splitPoint);
        valstring = pair.substr(splitPoint + 1);

        if (fieldname == "minLum") {
            lum = atof(valstring.c_str());
        } else if (fieldname == "blurRad") {
            blurRad = atof(valstring.c_str());
        } else if (fieldname == "pointX") {
            pointX = atof(valstring.c_str());
        } else if (fieldname == "pointY") {
            pointY = atof(valstring.c_str());
        } else if (fieldname == "pointZ") {
            pointZ = atof(valstring.c_str());
        }
    }
    /*
    cout << "lum: " << lum << endl;
    cout << "blurRad: " << blurRad << endl;
    cout << "x: " << pointX << endl;
    cout << "y: " << pointY << endl;
    cout << "z: " << pointZ << endl;
    */
    
    vector<const StarTree*> searchList{&tree};
    vector<uint64_t> foundNodes;

    visibleOctantsMagic(Vector3d(pointX, pointY, pointZ),
                        lum, blurRad,
                        searchList, foundNodes);

    //cout << "Star search complete" << endl;
    
    Json::Value root;
    for (vector<uint64_t>::iterator it = foundNodes.begin();
         it != foundNodes.end();
         ++it) {
        root.append(Json::Value(static_cast<Json::Value::UInt64>(*it)));
    }
    //cout << "Done making JSON" << endl;
    //cout << "----------" << endl;

    stringstream jsonStream;
    jsonStream << root;
    *response << "HTTP/1.1 200 OK\r\n"
              << "Content-Length: " << jsonStream.str().length()
              << "\r\n\r\n" << jsonStream.str();
}

void getNodeStarsHandler(HttpServer& server,
                         shared_ptr<HttpServer::Response> response,
                         shared_ptr<HttpServer::Request> request,
                         const map<uint64_t,const StarTree*>& treeMap) {
    //cout << "getNodeStars called!" << endl;
    string content = request->content.string();

    size_t pos;
    vector<uint64_t> getIndices;
    while ((pos = content.find(',')) != string::npos) {
        string indexStr = content.substr(0, pos);
        getIndices.push_back(strtoul(indexStr.c_str(), NULL, 10));
        content = content.substr(pos + 1);
    }
    getIndices.push_back(strtoul(content.c_str(), NULL, 10));
    
    Json::Value root(Json::objectValue);
    for (vector<uint64_t>::iterator ix = getIndices.begin();
         ix != getIndices.end(); ++ix) {
        Json::Value octantList;
        map<uint64_t,const StarTree*>::const_iterator t;
        t = treeMap.find(*ix);
        const vector<const Star*>& stars = (t->second)->stars();
        for (vector<const Star*>::const_iterator it = stars.begin();
             it != stars.end(); ++it) {
            const Star* pStar = *it;
            Json::Value star(Json::objectValue);
            star["sid"] = to_string(pStar->id());
            star["x"] = to_string(pStar->position().x());
            star["y"] = to_string(pStar->position().y());
            star["z"] = to_string(pStar->position().z());
            star["lum"] = to_string(pStar->lum());
            star["r"] = to_string(static_cast<int>(pStar->color()[0]));
            star["g"] = to_string(static_cast<int>(pStar->color()[1]));
            star["b"] = to_string(static_cast<int>(pStar->color()[2]));
            octantList.append(move(star));
        }
        root[to_string(*ix)] = move(octantList);
    }

    //cout << "Done making JSON" << endl;

    stringstream jsonStream;    
    jsonStream << root;
    *response << "HTTP/1.1 200 OK\r\n"
              << "Content-Length: " << jsonStream.str().length()
              << "\r\n\r\n" << jsonStream.str();
}

void dflt_res_send(const HttpServer &server,
                   const shared_ptr<HttpServer::Response> &response,
                   const shared_ptr<ifstream> &ifs) {
    //read and send 128 KB at a time
    static vector<char> buffer(131072); // Safe when server is running on one thread
    streamsize read_length;
    
    if((read_length =
        ifs->read(&buffer[0], buffer.size()).gcount()) > 0) {
        
        response->write(&buffer[0], read_length);
        if(read_length == static_cast<streamsize>(buffer.size())) {
            server.send(response,
                        [&server,
                         response,
                         ifs](const boost::system::error_code &ec) {
                            if(!ec)
                                dflt_res_send(server, response,
                                              ifs);
                            else
                                cerr << "Connection interrupted" << endl;
                        });
        }
    }
}

void dflt_res_request_handler(HttpServer& server,
                              shared_ptr<HttpServer::Response> response,
                              shared_ptr<HttpServer::Request> request) {
    auto web_root_path = boost::filesystem::canonical("static");
    boost::system::error_code ec;
    auto path =  boost::filesystem::canonical(web_root_path /
                                              request->path,
                                              ec);
    if (ec != boost::system::errc::success) {
        string content = "Could not open path " +
            request->path + ", file does not exist.";
        *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: "
                  << content.length() << "\r\n\r\n" << content;
        return;
    }
    
    //Check if path is within web_root_path
    if(distance(web_root_path.begin(), web_root_path.end()) >
       distance(path.begin(), path.end()) ||
       !equal(web_root_path.begin(), web_root_path.end(),
              path.begin())) {
        string content = "Could not open path " +
            request->path + ", path must be within web root.";
        *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: "
                  << content.length() << "\r\n\r\n" << content;
        return;
    }
    // Check if they requested a directory
    if(boost::filesystem::is_directory(path))
        path/="index.html";
    
    // Check if the file is a normal file
    if(!boost::filesystem::is_regular_file(path)) {
        string content = "Could not open path " +
            request->path + ", file does not exist.";
        *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: "
                  << content.length() << "\r\n\r\n" << content;
        return;
    }

    auto ifs = make_shared<ifstream>();
    ifs->open(path.string(), ifstream::in | ios::binary);
    if (*ifs) {
        ifs->seekg(0, ios::end);
        auto length = ifs->tellg();

        ifs->seekg(0, ios::beg);

        *response << "HTTP/1.1 200 OK\r\nContent-Length: "
                  << length << "\r\n\r\n";
        dflt_res_send(server, response, ifs);
    } else {
        string content = "Could not open path " +
            request->path + ", could not read file.";
        *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: "
                  << content.length() << "\r\n\r\n" << content;
        return;
    }
}
