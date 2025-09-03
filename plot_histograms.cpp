#include "DTNtupleTPGSimAnalyzer.h"

void plot_histograms() {

    // Open the two ROOT files
    TFile *fileNoRPC = TFile::Open("output/noRPC/DTNtupleTPGSimAnalyzer_Efficiency.root");
    TFile *fileRPC = TFile::Open("output/RPC/DTNtupleTPGSimAnalyzer_Efficiency.root");
    TFile *fileRPCPhase2 = TFile::Open("output/RPCPHASE2/DTNtupleTPGSimAnalyzer_Efficiency.root");

    if (!fileNoRPC || !fileRPC) {
        std::cout << "Error: Could not open one or both files!" << std::endl;
        return;
    }

    std::vector<std::string> algoTag  = {"AM", "AM+RPC"};
    // std::vector<std::string> totalTag = {"matched", "total"};
    std::vector<std::string> chambTag = {"MB1", "MB2", "MB3", "MB4"};
    std::vector<std::string> wheelTag = {"Wh.-2","Wh.-1","Wh.0","Wh.+1","Wh.+2",};

    std::string effDir  = "output/noRPC/histograms/effPlots/";
    std::string effDir2 = "output/RPC/histograms/effPlots/";

    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(effDir.c_str())) {
        gSystem->mkdir(effDir.c_str(), true); // true = recursive
    }
    if (gSystem->AccessPathName(effDir2.c_str())) {
        gSystem->mkdir(effDir2.c_str(), true); // true = recursive
    }

    // -------------------------------------------
    // MAKING EFFICIENCY PLOTS
    // -------------------------------------------
    TH1F *hTotal;
    TH1F *hMatched;
    std::string hName = "";
    for (int i = 0; i < 4; ++i){
        for (const auto & algo : algoTag)
        {
            int chamberNumber = i+1;
            hName = "hEff_MB" + std::to_string(chamberNumber) + "_"+algo;

            // NoRPC
            hTotal =   (TH1F*)fileNoRPC->Get((hName+"_total").c_str());
            hMatched = (TH1F*)fileNoRPC->Get((hName+"_matched").c_str());
            plot_eff( hName, hMatched, hTotal, effDir);

            // RPC
            hTotal =   (TH1F*)fileRPC->Get((hName+"_total").c_str());
            hMatched = (TH1F*)fileRPC->Get((hName+"_matched").c_str());
            plot_eff( hName, hMatched, hTotal, effDir2 );    
        }
    }

    hName = "EffEtaGenSeg";
    hTotal =   (TH1F*)fileNoRPC->Get((hName+"_total").c_str());
    hMatched = (TH1F*)fileNoRPC->Get((hName+"_matched").c_str());
    plot_eff( hName, hMatched, hTotal, effDir);
    plot_eff( hName, hMatched, hTotal, effDir2);

    hName = "EffEtaGenSeg20";
    hTotal =   (TH1F*)fileNoRPC->Get((hName+"_total").c_str());
    hMatched = (TH1F*)fileNoRPC->Get((hName+"_matched").c_str());
    plot_eff( hName, hMatched, hTotal, effDir);
    plot_eff( hName, hMatched, hTotal, effDir2);

    // std::string hName = "hEff_MB" + std::to_string(chamberNumber) + "_"+algo;

    
    //m_plots["EffEta_" + chambTag + "_AM_matched"]->Fill(gen_eta->at(iGenPart));
    
    // ----------------------------------------------------------
    // ----Time of the TPs associated with prompt muons [ns]-----
    // ----------------------------------------------------------
    std::string saveDir = "output/t0/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) {
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    TH1F *hist1;
    TH1F *hist2;
    TH1F *hist3;
    for (const auto & wheel : wheelTag) {
        for (const auto & chamb : chambTag) {
            
            std::string hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";
            hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
            hist2 = (TH1F*)fileRPC->Get(hName.c_str());

            std::string wheel2 = wheel;
            wheel2 = wheel2.erase(1, 2);  // Removes "W.": "Wh.-2"→ "W-2"

            plot_t0_histograms( hist1, hist2, 
                                "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched", 
                                "Time of the TPs associated with prompt muons [ns]", 
                                (wheel2+" "+chamb).c_str(),
                                saveDir, 
                                true);

        }
    }

    for (const auto & wheel : wheelTag) {
        for (const auto & chamb : chambTag) {
            
            std::string hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";
            hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
            hist2 = (TH1F*)fileRPC->Get(hName.c_str());
            hist3 = (TH1F*)fileRPCPhase2->Get(hName.c_str());

            std::string wheel2 = wheel;
            wheel2 = wheel2.erase(1, 2);  // Removes "W.": "Wh.-2"→ "W-2"

            plot_t0_histogramsV2( hist1, hist2, hist3,
                                "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched", 
                                "Time of the TPs associated with prompt muons [ns]", 
                                (wheel2+" "+chamb).c_str(),
                                saveDir, 
                                true);

        }
    }

    

    for (const auto & wheel : wheelTag) {
        for (const auto & chamb : chambTag) {
            
            std::string hName = "hPh2TpgPhiEmuAmBX"+wheel+chamb+"_matched";
            hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
            hist2 = (TH1F*)fileRPC->Get(hName.c_str());

            std::string wheel2 = wheel;
            wheel2 = wheel2.erase(1, 2);  // Removes "W.": "Wh.-2"→ "W-2"

            plot_BX_histograms( hist1, hist2, 
                                "hPh2TpgPhiEmuAmBX"+wheel+chamb+"_matched", 
                                "BX of the TPs associated with prompt muons [ns]", 
                                (wheel2+" "+chamb).c_str(),
                                saveDir, 
                                false);

        }
    }

    // for (const auto & wheel : wheelTag) {
    //     for (const auto & chamb : chambTag) {
            
    //         std::string hName = "hPh2TpgPhiEmuAmBX"+wheel+chamb+"_matched";
    //         hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
    //         hist2 = (TH1F*)fileRPC->Get(hName.c_str());

    //         std::string wheel2 = wheel;
    //         wheel2 = wheel2.erase(1, 2);  // Removes "W.": "Wh.-2"→ "W-2"

    //         plot_BX_histograms( hist1, hist2, 
    //                             "hPh2TpgPhiEmuAmBX"+wheel+chamb+"_matched", 
    //                             "BX of the TPs associated with prompt muons [ns]", 
    //                             (wheel2+" "+chamb).c_str(),
    //                             saveDir, 
    //                             false);

    //     }
    // }

    fileNoRPC = TFile::Open("output/RPCPHASE2noRPC/DTNtupleTPGSimAnalyzer_Efficiency.root");
    fileRPC = TFile::Open("output/RPCPHASE2/DTNtupleTPGSimAnalyzer_Efficiency.root");

    saveDir = "output/histogram_comparison/";
    hName = "hNSeg";
    hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
    hist2 = (TH1F*)fileRPC->Get(hName.c_str());
    hist3 = (TH1F*)fileRPCPhase2->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            hist3,
                            "hNSeg", 
                            "hNSeg", 
                            "",
                            saveDir, 
                            false);

    hName = "hNTrigs";
    hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
    hist2 = (TH1F*)fileRPC->Get(hName.c_str());
    hist3 = (TH1F*)fileRPCPhase2->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            hist3,
                            "hNTrigs", 
                            "NTrigs", 
                            "",
                            saveDir, 
                            false);

    hName = "hRatioNtpNseg_total";
    hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
    hist2 = (TH1F*)fileRPC->Get(hName.c_str());
    hist3 = (TH1F*)fileRPCPhase2->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            hist3,
                            "hRatioNtpNseg_total", 
                            "hRatioNtpNseg_total", 
                            "",
                            saveDir, 
                            false);


    // std::string hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";
    // hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
    // hist2 = (TH1F*)fileRPC->Get(hName.c_str());
    // plot_t0_histograms( hist1, hist2, 
    //                     "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched", 
    //                     "Time of the TPs associated with prompt muons [ns]", 
    //                     (wheel2+" "+chamb).c_str(),
    //                     saveDir, 
    //                     true);
        // EffEtaGenSeg_total
        // EffEtaGenSeg_matched

        // EffEtaGenSeg20_total
        // EffEtaGenSeg20_matched


    std::cout << "--------------------------------" << std::endl;
    std::cout << "END PROGRAM" << std::endl;
    std::cout << "--------------------------------" << std::endl;

}