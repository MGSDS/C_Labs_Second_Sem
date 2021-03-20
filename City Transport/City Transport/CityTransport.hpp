//
//  CityTransport.hpp
//  City Transport
//
//  Created by Bill Williams on 2/27/21.
//

#ifndef CityTransport_hpp
#define CityTransport_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "pugixml/pugixml.hpp"
#include <cstring>
#include <map>


struct Stop{
    struct coordinates{
        float lat;
        float lon;
    };
    std::string type_of_vehicle;
    std::string object_type;
    std::string name_stopping;
    std::string the_official_name;
    std::string location;
    std::vector<std::string> routes;
    coordinates coords;
};

class Route{
    std::string vecType_;
    std::string route_;
    std::vector<Stop*> stops_;
    std::vector<Stop*> final_;
    double length_;
    size_t sz;
public:
    Route(const std::string& route, const std::string& vecType, std::vector<Stop>& data, std::map<std::string, size_t>& stopsPerLocation);
    Route() : vecType_("NULL"), route_("NULL"), sz(0), length_(0){}
    double getLength() const {return length_;}
    size_t stopsCount() const {return sz;}
    const std::string* getRoute() const {return &route_;}
private:
    void calcLength();
    double getDistance(Stop::coordinates a, Stop::coordinates b);
    double deg2rad(double deg);
    double rad2deg(double rad);
    double findMinimalDist(Stop* curr, std::vector<Stop*>& stops);
};

class CityTransport {
    std::vector<Stop> data;
    std::map<std::string, std::map<std::string, Route>> transport_;
    std::map<std::string, size_t> stopsPerLocation_;
public:
    CityTransport(const std::vector<Stop>& data);
    CityTransport(const CityTransport& obj) = delete;
    CityTransport operator=(const CityTransport& obj) = delete;
    const Route* getLongestRide(const std::string& vecType) const;
    const Route* getRideMaxStopsCount(const std::string& vecType) const;
    std::pair<std::string, size_t> getMaxStopsStreet() const;
private:
    std::vector<std::string> get_routes_list(const std::vector<Stop>& data);
    std::vector<std::string> get_locations(const std::vector<Stop>& data);
};

class XmlReader{
    std::vector<Stop> stations;
    pugi::xml_document doc;
public:
    XmlReader(const std::string& file_name);
    void read();
    std::vector<Stop> getStopsVector()const;
};


#endif /* CityTransport_hpp */

