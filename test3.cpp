#include "DTNtupleTPGSimAnalyzer.h"


// class BarrelGeo {  // The class
//   private:  // Access specifier
//     std::vector<std::vector<double>> barrel_geometry; // Attribute

//   public:          
//     BarrelGeo(const std::string& filename) { // Constructor
//         cout << "Testing!!!!";
//         std::ifstream file(filename);

//         if (!file.is_open()) {
//             std::cerr << "Error: Cannot open file " << filename << std::endl;
//             // return chambers;  // Return empty vector
//         }

//         std::string line;
//         int line_number = 0;
        
//         while (std::getline(file, line)) {
//             line_number++;
            
//             // Skip header lines (lines 1-3)
//             if (line_number <= 3) {
//                 continue;
//             }
//             // Skip empty lines
//             if (line.empty()) {
//                 continue;
//             }
            
//             // Parse the data line
//             std::istringstream iss(line);
//             int station, layer, sector, ring;
//             double eta_min, eta_max, phi_min, phi_max;
            
//             if (iss >> station >> layer >> sector >> ring 
//                     >> eta_min >> eta_max >> phi_min >> phi_max) {
                
//                 // std::cout << station << " " << layer << " " << sector << " " 
//                 //             << ring << " " << eta_min << " " << eta_max << " " 
//                 //             <<phi_min << " " << phi_max << std::endl;

//                 std::vector<double> tempVec; // tempVec = [station] [layer] [ring] [eta_min] [eta_max] [phi_min] [phi_max] 
//                 tempVec.push_back(station);
//                 tempVec.push_back(layer);
//                 tempVec.push_back(sector);
//                 tempVec.push_back(ring);
//                 tempVec.push_back(eta_min);
//                 tempVec.push_back(eta_max);
//                 tempVec.push_back(phi_min);
//                 tempVec.push_back(phi_max);
//                 barrel_geometry.push_back(tempVec); 
//             } else {
//                 std::cerr << "Warning: Could not parse line " << line_number << ": " << line << std::endl;
//             }
//         } // End loop file lines
//     }

//     std::vector<std::vector<double>> StaLaySecRing(double genEta, double genPhi){

//         std::vector<std::vector<double>> geo_info;

//         // 0=[station] 1=[layer] 2=[sector] 3=[ring] 4=[eta_min] 5=[eta_max] 6=[phi_min] 7=[phi_max]
//         for (size_t iGeo = 0; iGeo < barrel_geometry.size(); ++iGeo) {
            
//             double geoEtaMin = barrel_geometry[iGeo][4];
//             double geoEtaMax = barrel_geometry[iGeo][5];
//             double geoPhiMin = barrel_geometry[iGeo][6];
//             double geoPhiMax = barrel_geometry[iGeo][7];

//             if ( genEta < geoEtaMin) continue;
//             if ( genEta > geoEtaMax) continue;
//             if ( genPhi < geoPhiMin) continue;
//             if ( genPhi > geoPhiMax) continue;
//             int geoStation = barrel_geometry[iGeo][0];
//             int geoLayer   = barrel_geometry[iGeo][1];
//             int geoSector  = barrel_geometry[iGeo][2];
//             int geoRing    = barrel_geometry[iGeo][3];
//             // std::cout << "Ring:" << geoRing << ", Sector: " << geoSector << ", Station: " << geoStation << ", Leyer: " << geoLayer << std::endl;
            
//             std::vector<double> tempVec; // tempVec = [station] [layer] [ring]
//             tempVec.push_back(geoStation);
//             tempVec.push_back(geoLayer);
//             tempVec.push_back(geoSector);
//             tempVec.push_back(geoRing);
//             geo_info.push_back(tempVec);

//         }

//         return geo_info;
//     }

// }; // End Class

int test3() {

    BarrelGeo barGeo("barrel_geometry.txt");

    std::vector<std::vector<double>> gen_test = { //[pt][eta][phi]
        {59.9677, 0.303135, -1.73079},
        {59.9677, -0.303135, 1.41081},
        {188.142, -0.351275, 2.0767},
        {188.142, 0.351275, -1.06489},
        {33.8774, -0.251606, -0.332262},
        {33.8774, 0.251606, -2.80933},
        {51.2031, 0.06783, -1.67888},
        {51.2031, -0.06783, -1.46271}
    };

    for (size_t iGenPart = 0; iGenPart < gen_test.size(); ++iGenPart) {

        double genPt = gen_test[iGenPart][0];
        double genEta = gen_test[iGenPart][1];
        double genPhi = gen_test[iGenPart][2];

        std::cout << "------------------------------------------------------"  << std::endl;
        std::cout << "iGenPart:" << iGenPart << ", genPt: " << genPt << ", genEta: " << genEta << ", genPhi: " << genPhi << std::endl;

        std::vector<std::vector<double>> geo_info = barGeo.StaLaySecRing(genEta,genPhi);

        for (size_t iGeo = 0; iGeo < geo_info.size(); ++iGeo) {
            // 0=[station] 1=[layer] 2=[sector] 3=[ring]
            int geoStation = geo_info[iGeo][0];
            int geoLayer   = geo_info[iGeo][1];
            int geoSector  = geo_info[iGeo][2];
            int geoRing    = geo_info[iGeo][3];
            std::cout << "Ring:" << geoRing << ", Sector: " << geoSector << ", Station: " << geoStation << ", Leyer: " << geoLayer << std::endl;
        }
 
    }



    return 0;

}