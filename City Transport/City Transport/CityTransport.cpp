//
//  CityTransport.cpp
//  City Transport
//
//  Created by Bill Williams on 2/27/21.
//

#include "CityTransport.hpp"
#include <iostream>

//честно ********** не считается украденным
class splitstring : public std::string {
    std::vector<std::string> flds;
public:
    splitstring(const std::string &s) : std::string(s) { };
    std::vector<std::string>& split(char delim, int rep=0);
};

std::vector<std::string>& splitstring::split(char delim, int rep) {
    if (!flds.empty()) flds.clear();
    std::string work = data();
    std::string buf = "";
    int i = 0;
    while (i < work.length()) {
        if (work[i] != delim)
            buf += work[i];
        else if (rep == 1) {
            flds.push_back(buf);
            buf = "";
        } else if (buf.length() > 0) {
            flds.push_back(buf);
            buf = "";
        }
        i++;
    }
    if (!buf.empty())
        flds.push_back(buf);
    return flds;
}

XmlReader::XmlReader(const std::string& file_name){
    pugi::xml_parse_result result = doc.load_file(file_name.c_str());
    if (!result)
        throw std::bad_exception();
}

void XmlReader::read(){
    pugi::xml_node node = doc.child("dataset").child("transport_station");
    Stop tmp;
    std::string routes;
    std::vector<std::string> coords;
    while(node){
        tmp.type_of_vehicle = node.child("type_of_vehicle").first_child().value();
        tmp.object_type = node.child("object_type").first_child().value();
        tmp.name_stopping = node.child("name_stopping").first_child().value();
        tmp.the_official_name = node.child("the_official_name").first_child().value();
        tmp.location = node.child("location").first_child().value();
        routes = node.child("routes").first_child().value();
        
        splitstring spl(routes.c_str());
        
        if(std::find(routes.begin(), routes.end(), ',') != routes.end())
            tmp.routes = spl.split(',');
        else
            tmp.routes = spl.split(' ');
        
        spl = splitstring(node.child("coordinates").first_child().value());
        
        coords = spl.split(',');
        
        tmp.coords.lat = std::stof(coords.at(0));
        tmp.coords.lon = std::stof(coords.at(1));
        
        stations.push_back(tmp);
        node = node.next_sibling();
    }
}

std::vector<Stop> XmlReader::getStopsVector()const{
    return stations;
}

Route::Route(const std::string& route, const std::string& vecType, std::vector<Stop>& data, std::map<std::string, size_t>& stopsPerLocation) : route_(route), vecType_(vecType), sz(0), length_(0){
    for (int i = 0; i < data.size(); ++i) {
        if((std::find(data.at(i).routes.begin(), data.at(i).routes.end(), route_) != data.at(i).routes.end()) && (data.at(i).type_of_vehicle == vecType_)){
            
            stops_.push_back(&data.at(i));
            std::vector<std::string> location = splitstring(data.at(i).location).split(',');
            for ( std::string j : location) {
                stopsPerLocation.at(j)++;
            }
            sz++;
        }
    }
    if(sz != 0){
        calcLength();
    }
    
}


double Route::deg2rad(double deg) {
  return (deg * M_PI / 180);
}


double Route::rad2deg(double rad) {
  return (rad * 180 / M_PI);
}

double Route::getDistance(Stop::coordinates a, Stop::coordinates b){
    double lat1r, lon1r, lat2r, lon2r, u, v;
      lat1r = deg2rad(a.lat);
      lon1r = deg2rad(a.lon);
      lat2r = deg2rad(b.lat);
      lon2r = deg2rad(b.lon);
      u = sin((lat2r - lat1r)/2);
      v = sin((lon2r - lon1r)/2);
      return 2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

double Route::findMinimalDist(Stop* curr, std::vector<Stop*>& stops){
//    std::vector<Stop*>::iterator min = stops.end();
    Stop* min = nullptr;
    double locallength = std::numeric_limits<double>::max();
//    for (auto i = stops.begin(); i < stops.end(); i++) {
    for(Stop* j : stops){
        double dist = getDistance(curr->coords, j->coords);
        if((dist < locallength) && (j != curr)){
            min = j;
            locallength = dist;
        }
    }
    if(min == nullptr)
        return 0;
    curr = min;
    stops.erase(std::find(stops.begin(), stops.end(), min));
    return locallength;
}

void Route::calcLength(){
    std::vector<std::vector<float>> stops(stops_.size(), std::vector<float>(stops_.size()));
    for (int i = 0; i < stops_.size(); ++i) {
        for (int j = 0; j < stops_.size(); ++j) {
            stops.at(i).at(j) = getDistance(stops_.at(i)->coords, stops_.at(j)->coords);
        }
    }
    std::vector<float> dist(stops_.size(), std::numeric_limits<float>::max());
        std::vector<bool> visited (stops_.size(), false);
     
        float res = 0;
     
        dist.at(0) = 0;
     
        for (int i = 0; i < stops_.size(); ++i){
            float min = std::numeric_limits<float>::max();
            int minpos = 0;
            for(int j = 0; j < stops_.size(); ++j){
                if(!visited.at(j) && dist.at(j) < min){
                    min = dist.at(j);
                    minpos = j;
                }
            }
            res += min;
            visited.at(minpos) = true;
            for (int j = 0; j < stops_.size(); ++j) {
                dist.at(j) = std::min(dist.at(j), stops.at(minpos).at(j));
            }
            this->length_ = res;
        }
}

CityTransport::CityTransport(const std::vector<Stop>& dat){
//    Автобус Трамвай Троллейбус
    data = dat;
    std::vector<std::string> stops = get_routes_list(data);
    std::vector<std::string> locations = get_locations(data);
    for (std::string i : locations) {
        stopsPerLocation_.insert({i, 0});
    }
    std::map<std::string, Route> stopsListBus;
    std::map<std::string, Route> stopsListTram;
    std::map<std::string, Route> stopsListTroll;
    {
        for (std::string i : stops) {
            Route tmpBus(i, "Автобус", data, stopsPerLocation_);
            Route tmpTram(i, "Трамвай", data, stopsPerLocation_);
            Route tmpTroll(i, "Троллейбус", data, stopsPerLocation_);
            if(tmpBus.stopsCount() != 0)
                stopsListBus.insert({i, tmpBus});
            if(tmpTram.stopsCount() != 0)
                stopsListTram.insert({i, tmpTram});
            if(tmpTroll.stopsCount() != 0)
                stopsListTroll.insert({i, tmpTroll});
        }
        transport_.insert({"Автобус", stopsListBus});
        transport_.insert({"Трамвай", stopsListTram});
        transport_.insert({"Троллейбус", stopsListTroll});
    }
}

std::vector<std::string> CityTransport::get_routes_list(const std::vector<Stop>& data){
    std::vector<std::string> routes;
    for (Stop i : data) {
        for (std::string j : i.routes) {
            routes.push_back(j);
        }
    }
    std::sort(routes.begin(), routes.end());
    std::vector<std::string>::iterator it;
    it = unique(routes.begin(), routes.end());
    routes.resize(distance(routes.begin(),it));
    return routes;
}

std::vector<std::string> CityTransport::get_locations(const std::vector<Stop>& data){
    std::vector<std::string> locations;
    for (Stop i : data) {
        splitstring spl(i.location);
        for(std::string j : spl.split(','))
            locations.push_back(j);
    }
    std::sort(locations.begin(), locations.end());
    std::vector<std::string>::iterator it;
    it = unique(locations.begin(), locations.end());
    locations.resize(distance(locations.begin(),it));
    return locations;
}

const Route* CityTransport::getLongestRide(const std::string& vecType) const{
    auto x = std::max_element(transport_.at(vecType).begin(), transport_.at(vecType).end(),
        [](const std::pair<std::string, Route>& p1, const std::pair<std::string, Route>& p2) {
            return p1.second.getLength() < p2.second.getLength(); });
    return &(x->second);
}
const Route* CityTransport::getRideMaxStopsCount(const std::string& vecType) const{
    auto x = std::max_element(transport_.at(vecType).begin(), transport_.at(vecType).end(),
        [](const std::pair<std::string, Route>& p1, const std::pair<std::string, Route>& p2) {
            return p1.second.stopsCount() < p2.second.stopsCount(); });
    return &(x->second);
}

std::pair<std::string, size_t> CityTransport::getMaxStopsStreet() const{
    auto x = std::max_element(stopsPerLocation_.begin(), stopsPerLocation_.end(),
        [](const std::pair<std::string, size_t>& p1, const std::pair<std::string, size_t>& p2) {
            return p1.second < p2.second; });
    return *x;
}
