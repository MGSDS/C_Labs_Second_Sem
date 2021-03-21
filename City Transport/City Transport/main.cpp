//
//  main.cpp
//  City Transport
//
//  Created by Bill Williams on 2/27/21.
//

#include <iostream>
#include "CityTransport.hpp"




int main(int argc, const char * argv[]) {
    std::string path;
    getline(std::cin, path);
    auto start = std::chrono::system_clock::now();
    XmlReader reader(path);
    reader.read();
    std::vector<Stop> data = reader.getStopsVector();
    CityTransport tr(data);
    const Route* LongestBus = tr.getLongestRide("Автобус");
    const Route* LongestTram = tr.getLongestRide("Трамвай");
    const Route* LongestTroll = tr.getLongestRide("Троллейбус");
    const Route* maxStopsCountBus = tr.getRideMaxStopsCount("Автобус");
    const Route* maxStopsCountTram = tr.getRideMaxStopsCount("Трамвай");
    const Route* maxStopsCountTroll = tr.getRideMaxStopsCount("Троллейбус");
    auto maxStopsPerStreet = tr.getMaxStopsStreet();
    std::cout << "Longest rides:" << std::endl;
    std::cout << "    Автобуc: №" << *(LongestBus->getRoute()) << " length: " << LongestBus->getLength() << std::endl;
    std::cout << "    Трамвай: №" << *(LongestTram->getRoute()) << " length: " << LongestTram->getLength() << std::endl;
    std::cout << "    Троллейбус: №" << *(LongestTroll->getRoute()) << " length: " << LongestTroll->getLength() << std::endl;
    std::cout << "Rides with max stops count" << std::endl;
    std::cout << "    Автобуc: №" << *(maxStopsCountBus->getRoute()) << " stops count: " << maxStopsCountBus->stopsCount() << std::endl;
    std::cout << "    Трамвай: №" << *(maxStopsCountTram->getRoute()) << " stops count: " << maxStopsCountTram->stopsCount() << std::endl;
    std::cout << "    Троллейбус: №" << *(maxStopsCountTroll->getRoute()) << " stops count: " << maxStopsCountTroll->stopsCount() << std::endl;
    std::cout << "Street with max stops count:" << std::endl;
    std::cout << "    " << maxStopsPerStreet.first << " stops count: " << maxStopsPerStreet.second << std::endl;
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
            << "elapsed time: " << elapsed_seconds.count() << "s\n";
    
    return 0;
}

