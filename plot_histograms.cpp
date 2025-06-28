#include "DTNtupleTPGSimAnalyzer.h"






void plot_histograms() {

    // Open the two ROOT files
    TFile *fileNoRPC = TFile::Open("output/noRPC/DTNtupleTPGSimAnalyzer_Efficiency.root");
    TFile *fileRPC = TFile::Open("output/RPC/DTNtupleTPGSimAnalyzer_Efficiency.root");

    if (!fileNoRPC || !fileRPC) {
        std::cout << "Error: Could not open one or both files!" << std::endl;
        return;
    }

    std::vector<std::string> algoTag  = {"AM", "AM+RPC"};
    // std::vector<std::string> totalTag = {"matched", "total"};
    std::vector<std::string> chambTag = {"MB1", "MB2", "MB3", "MB4"};
    std::vector<std::string> wheelTag = {"Wh.-2","Wh.-1","Wh.0","Wh.+1","Wh.+2",};

    TH1F *hist1;
    TH1F *hist2;

    // -------------------------------------------
    // MAKING EFFICIENCY PLOTS
    // -------------------------------------------
    for (int i = 0; i < 4; ++i){
        for (const auto & algo : algoTag2)
        {
            int chamberNumber = i+1;

            // Get the histograms from your map
            std::string hname = "Eff_MB" + std::to_string(chamberNumber) + "_"+algo+"_total";



        }


    }


    // ----------------------------------------------------------
    // ----Time of the TPs associated with prompt muons [ns]-----
    // ----------------------------------------------------------
    for (const auto & chamb : chambTag) {
        for (const auto & wheel : wheelTag) {
            
            hist1 = (TH1F*)fileNoRPC->Get(("hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched").c_str());
            hist2 = (TH1F*)fileRPC->Get(("hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched").c_str());

            std::string wheel2 = wheel;
            wheel2 = wheel2.erase(1, 2);  // Removes "W.": "Wh.-2"→ "W-2"

            plot_two_histograms_function(  hist1, hist2, 
                                            "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched", 
                                            "Time of the TPs associated with prompt muons [ns]", (wheel2+" "+chamb).c_str(), 
                                            true);

        }
    }


    std::cout << "--------------------------------" << std::endl;
    std::cout << "END PROGRAM" << std::endl;
    std::cout << "--------------------------------" << std::endl;

}