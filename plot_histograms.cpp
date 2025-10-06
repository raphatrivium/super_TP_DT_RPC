#include "DTNtupleTPGSimAnalyzer.h"

void plot_histograms() {

    // Open the two ROOT files
    TFile *fileNoRPC = TFile::Open("output/noRPC/DTNtupleTPGSimAnalyzer_Efficiency.root");
    TFile *fileRPC = TFile::Open("output/RPC/DTNtupleTPGSimAnalyzer_Efficiency.root");
    TFile *fileNoRPCUpdated = TFile::Open("output/noRPCUpdated/DTNtupleTPGSimAnalyzer_Efficiency.root");
    TFile *fileRPCUpdated = TFile::Open("output/RPCUpdated/DTNtupleTPGSimAnalyzer_Efficiency.root");


    if (!fileNoRPC || !fileRPC) {
        std::cout << "Error: Could not open one or both files!" << std::endl;
        return;
    }

    std::vector<std::string> algoTag  = {"AM", "AM+RPC"};
    // std::vector<std::string> totalTag = {"matched", "total"};
    std::vector<std::string> chambTag = {"MB1", "MB2", "MB3", "MB4"};
    std::vector<std::string> wheelTag = {"Wh.-2","Wh.-1","Wh.0","Wh.+1","Wh.+2",};

    std::vector<std::string> effDir = {
                                       "output/noRPC/histograms/effPlots/",
                                       "output/RPC/histograms/effPlots/",
                                       "output/noRPCUpdated/histograms/effPlots/", 
                                       "output/RPCUpdated/histograms/effPlots/",
                                    };

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
            plot_eff( hName, hMatched, hTotal, effDir[0]);

            // RPC
            hTotal =   (TH1F*)fileRPC->Get((hName+"_total").c_str());
            hMatched = (TH1F*)fileRPC->Get((hName+"_matched").c_str());
            plot_eff( hName, hMatched, hTotal, effDir[1] );    
        }
    }

    hName = "EffEtaGenSeg";
    hTotal =   (TH1F*)fileNoRPC->Get((hName+"_total").c_str());
    hMatched = (TH1F*)fileNoRPC->Get((hName+"_matched").c_str());
    plot_eff( hName, hMatched, hTotal, effDir[0]);
    hTotal =   (TH1F*)fileRPC->Get((hName+"_total").c_str());
    hMatched = (TH1F*)fileRPC->Get((hName+"_matched").c_str());
    plot_eff( hName, hMatched, hTotal, effDir[1]);

    hName = "EffEtaGenSeg20";
    hTotal =   (TH1F*)fileNoRPC->Get((hName+"_total").c_str());
    hMatched = (TH1F*)fileNoRPC->Get((hName+"_matched").c_str());
    plot_eff( hName, hMatched, hTotal, effDir[0]);
    hTotal =   (TH1F*)fileRPC->Get((hName+"_total").c_str());
    hMatched = (TH1F*)fileRPC->Get((hName+"_matched").c_str());
    plot_eff( hName, hMatched, hTotal, effDir[1]);

    hName = "Eff_TPwheels";
    hTotal =   (TH1F*)fileNoRPC->Get((hName+"_total").c_str());
    hMatched = (TH1F*)fileNoRPC->Get((hName+"_matched").c_str());
    plot_eff( hName, hMatched, hTotal, effDir[0]);
    hTotal =   (TH1F*)fileRPC->Get((hName+"_total").c_str());
    hMatched = (TH1F*)fileRPC->Get((hName+"_matched").c_str());
    plot_eff( hName, hMatched, hTotal, effDir[1]);


    // hName = "Eff_TPnotMatched";
    // hTotal =   (TH1F*)fileNoRPC->Get((hName+"_total").c_str());
    // hMatched = (TH1F*)fileNoRPC->Get((hName+"_matched").c_str());
    // plot_eff( hName, hMatched, hTotal, effDir[0]);
    // hTotal =   (TH1F*)fileRPC->Get((hName+"_total").c_str());
    // hMatched = (TH1F*)fileRPC->Get((hName+"_matched").c_str());
    // plot_eff( hName, hMatched, hTotal, effDir[1]);
    // hTotal =   (TH1F*)fileNoRPCUpdated->Get((hName+"_total").c_str());
    // hMatched = (TH1F*)fileNoRPCUpdated->Get((hName+"_matched").c_str());
    // plot_eff( hName, hMatched, hTotal, effDir[2]);
    // hTotal =   (TH1F*)fileRPCUpdated->Get((hName+"_total").c_str());
    // hMatched = (TH1F*)fileRPCUpdated->Get((hName+"_matched").c_str());
    // plot_eff( hName, hMatched, hTotal, effDir[3]);
    
    std::string saveDir = "output/histogram_comparison/";
    
    hName = "Eff_TPwheels";
    TH1F *hTotal1 =   (TH1F*)fileNoRPC->Get((hName+"_total").c_str());
    TH1F *hMatched1 = (TH1F*)fileNoRPC->Get((hName+"_matched").c_str());
    TH1F *hTotal2 =   (TH1F*)fileRPC->Get((hName+"_total").c_str());
    TH1F *hMatched2 = (TH1F*)fileRPC->Get((hName+"_matched").c_str());
    plot_eff_fake_rate( hName, 
        hMatched1, hTotal1, hMatched2, hTotal2,
        saveDir);
        
    std::vector<std::string> secTags   = { "Sec1", "Sec2", "Sec3", "Sec4", "Sec5", "Sec6", "Sec7", "Sec8","Sec9","Sec10","Sec11","Sec12"};
    for (const auto & secTag : secTags)
    {
        hName = "Eff_TPwheels_"+secTag;
        hTotal1 =   (TH1F*)fileNoRPC->Get((hName+"_total").c_str());
        hMatched1 = (TH1F*)fileNoRPC->Get((hName+"_matched").c_str());
        hTotal2 =   (TH1F*)fileRPC->Get((hName+"_total").c_str());
        hMatched2 = (TH1F*)fileRPC->Get((hName+"_matched").c_str());
        plot_eff_fake_rate( hName, hMatched1, hTotal1, hMatched2, hTotal2, saveDir);
    }


    hName = "fakeRate_WheelStationTP";
    hTotal1 =   (TH1F*)fileNoRPC->Get((hName+"_total").c_str());
    hMatched1 = (TH1F*)fileNoRPC->Get((hName+"_matched").c_str());
    hTotal2 =   (TH1F*)fileRPC->Get((hName+"_total").c_str());
    hMatched2 = (TH1F*)fileRPC->Get((hName+"_matched").c_str());
    plot_eff_fake_rate( hName, 
                        hMatched1, hTotal1, hMatched2, hTotal2,
                        saveDir);    
                   

    hName = "fakeRate_TPnot";
    hTotal1 =   (TH1F*)fileNoRPC->Get((hName+"_total").c_str());
    hMatched1 = (TH1F*)fileNoRPC->Get((hName+"_matched").c_str());
    hTotal2 =   (TH1F*)fileRPC->Get((hName+"_total").c_str());
    hMatched2 = (TH1F*)fileRPC->Get((hName+"_matched").c_str());
    plot_eff_fake_rate( hName, 
                        hMatched1, hTotal1, hMatched2, hTotal2,
                        saveDir);

    for (const auto & secTag : secTags)
    {
        hName = "fakeRateTP_WheelvsStation_"+secTag;
        hTotal1 =   (TH1F*)fileNoRPC->Get((hName+"_total").c_str());
        hMatched1 = (TH1F*)fileNoRPC->Get((hName+"_matched").c_str());
        hTotal2 =   (TH1F*)fileRPC->Get((hName+"_total").c_str());
        hMatched2 = (TH1F*)fileRPC->Get((hName+"_matched").c_str());
        plot_eff_fake_rate( hName, hMatched1, hTotal1, hMatched2, hTotal2, saveDir);
    }



    
   

    
    saveDir = "output/histogram_comparison_RPCUpdate/";

    hName = "Eff_TPwheels";
    hTotal1 =   (TH1F*)fileNoRPCUpdated->Get((hName+"_total").c_str());
    hMatched1 = (TH1F*)fileNoRPCUpdated->Get((hName+"_matched").c_str());
    hTotal2 =   (TH1F*)fileRPCUpdated->Get((hName+"_total").c_str());
    hMatched2 = (TH1F*)fileRPCUpdated->Get((hName+"_matched").c_str());
    plot_eff_fake_rate( hName, 
                        hMatched1, hTotal1, hMatched2, hTotal2,
                        saveDir);


    hName = "fakeRate_WheelStationTP";
    hTotal1 =   (TH1F*)fileNoRPCUpdated->Get((hName+"_total").c_str());
    hMatched1 = (TH1F*)fileNoRPCUpdated->Get((hName+"_matched").c_str());
    hTotal2 =   (TH1F*)fileRPCUpdated->Get((hName+"_total").c_str());
    hMatched2 = (TH1F*)fileRPCUpdated->Get((hName+"_matched").c_str());
    plot_eff_fake_rate( hName, 
                        hMatched1, hTotal1, hMatched2, hTotal2,
                        saveDir);    
                   

    hName = "fakeRate_TPnot";
    hTotal1 =   (TH1F*)fileNoRPCUpdated->Get((hName+"_total").c_str());
    hMatched1 = (TH1F*)fileNoRPCUpdated->Get((hName+"_matched").c_str());
    hTotal2 =   (TH1F*)fileRPCUpdated->Get((hName+"_total").c_str());
    hMatched2 = (TH1F*)fileRPCUpdated->Get((hName+"_matched").c_str());
    plot_eff_fake_rate( hName, 
                        hMatched1, hTotal1, hMatched2, hTotal2,
                        saveDir);

    

    // hName = "Eff_TPnotMatched";
    // hTotal1 =   (TH1F*)fileNoRPCUpdated->Get((hName+"_total").c_str());
    // hMatched1 = (TH1F*)fileNoRPCUpdated->Get((hName+"_matched").c_str());
    // hTotal2 =   (TH1F*)fileRPCUpdated->Get((hName+"_total").c_str());
    // hMatched2 = (TH1F*)fileRPCUpdated->Get((hName+"_matched").c_str());
    // plot_eff_fake_rate( hName, 
    //                     hMatched1, hTotal1, hMatched2, hTotal2,
    //                     "output/histogram_comparison/");                    
    


    // ----------------------------------------------------------
    // ----Time of the TPs associated with prompt muons [ns]-----
    // ----------------------------------------------------------
    saveDir = "output/t0/";
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
            hist3 = (TH1F*)fileRPCUpdated->Get(hName.c_str());

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

    saveDir = "output/histogram_comparison/";
    hName = "hNSeg";
    hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
    hist2 = (TH1F*)fileRPC->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            "hNSeg", 
                            "", 
                            "",
                            saveDir, 
                            false);

    hName = "hNTrigs";
    hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
    hist2 = (TH1F*)fileRPC->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            "hNTrigs", 
                            "", 
                            "",
                            saveDir, 
                            false);

    hName = "hRatioNtpNseg_total";
    hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
    hist2 = (TH1F*)fileRPC->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            "hRatioNtpNseg_total", 
                            "", 
                            "",
                            saveDir, 
                            false);

    hName = "TPnotMatched";
    hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
    hist2 = (TH1F*)fileRPC->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            "TPnotMatched", 
                            "", 
                            "",
                            saveDir, 
                            false);

    hName = "TPMatched";
    hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
    hist2 = (TH1F*)fileRPC->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            "TPMatched", 
                            "", 
                            "",
                            saveDir, 
                            false);

    hName = "hTrigFlag";
    hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
    hist2 = (TH1F*)fileRPC->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            "hTrigFlag", 
                            "", 
                            "",
                            saveDir, 
                            false);

    hName = "hTPMatchedRPCflag";
    hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
    hist2 = (TH1F*)fileRPC->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            "hTPMatchedRPCflag", 
                            "", 
                            "",
                            saveDir, 
                            false);
                            
    // hName = "fakeRate_EventWheelStationTP_matched";
    // hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
    // hist2 = (TH1F*)fileRPC->Get(hName.c_str());
    // plot_normal_histograms( hist1, 
    //                         hist2, 
    //                         "fakeRate_EventWheelStationTP_matched", 
    //                         "", 
    //                         "",
    //                         saveDir, 
    //                         false);

    hName = "fakeRate_EventWheelStationTP_matched";
    hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
    hist2 = (TH1F*)fileRPC->Get(hName.c_str());
    plot_fakeRate_wheels_histograms( hist1, 
                            hist2, 
                            "fakeRate_EventWheelStationTP_matched", 
                            "", 
                            "",
                            saveDir, 
                            false);


    // for (const auto & secTag : secTags)
    // {
    //     hName = "fakeRate_EventWheelStationTP_"+secTag+"_matched";
    //     hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
    //     hist2 = (TH1F*)fileRPC->Get(hName.c_str());
    //     plot_normal_histograms( hist1, 
    //                         hist2, 
    //                         "fakeRate_EventWheelStationTP_"+secTag+"_matched", 
    //                         "", 
    //                         "",
    //                         saveDir, 
    //                         false);
    // }


    for (const auto & secTag : secTags)
    {
        hName = "fakeRate_EventWheelStationTP_"+secTag+"_matched";
        hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
        hist2 = (TH1F*)fileRPC->Get(hName.c_str());
        plot_fakeRate_wheels_histograms(hist1, 
                                        hist2, 
                                        "fakeRate_EventWheelStationTP_"+secTag+"_matched", 
                                        "", 
                                        "",
                                        saveDir, 
                                        false);
    }



    // -------------------------------------------------------------------------------
    saveDir = "output/histogram_comparison_RPCUpdate/";

    hName = "hNSeg";
    hist1 = (TH1F*)fileNoRPCUpdated->Get(hName.c_str());
    hist2 = (TH1F*)fileRPCUpdated->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            "hNSegRPCUpdated", 
                            "", 
                            "",
                            saveDir, 
                            false);

    hName = "hNTrigs";
    hist1 = (TH1F*)fileNoRPCUpdated->Get(hName.c_str());
    hist2 = (TH1F*)fileRPCUpdated->Get(hName.c_str());

    plot_normal_histograms( hist1, 
                            hist2, 
                            "hNTrigsRPCUpdated", 
                            "", 
                            "",
                            saveDir, 
                            false);

    hName = "hRatioNtpNseg_total";
    hist1 = (TH1F*)fileNoRPCUpdated->Get(hName.c_str());
    hist2 = (TH1F*)fileRPCUpdated->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            "hRatioNtpNseg_totalRPCUpdated", 
                            "", 
                            "",
                            saveDir, 
                            false);
    
    hName = "TPnotMatched";
    hist1 = (TH1F*)fileNoRPCUpdated->Get(hName.c_str());
    hist2 = (TH1F*)fileRPCUpdated->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            "TPnotMatchedRPCUpdated", 
                            "", 
                            "",
                            saveDir, 
                            false);

    hName = "TPMatched";
    hist1 = (TH1F*)fileNoRPCUpdated->Get(hName.c_str());
    hist2 = (TH1F*)fileRPCUpdated->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            "TPMatchedRPCUpdated", 
                            "", 
                            "",
                            saveDir, 
                            false);

    hName = "hTrigFlag";
    hist1 = (TH1F*)fileNoRPCUpdated->Get(hName.c_str());
    hist2 = (TH1F*)fileRPCUpdated->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            "hTrigFlagRPCUpdated", 
                            "", 
                            "",
                            saveDir, 
                            false);

    hName = "hTPMatchedRPCflag";
    hist1 = (TH1F*)fileNoRPCUpdated->Get(hName.c_str());
    hist2 = (TH1F*)fileRPCUpdated->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            "hTPMatchedRPCflagRPCUpdated", 
                            "", 
                            "",
                            saveDir, 
                            false);
                            
    hName = "fakeRate_EventWheelStationTP_matched";
    hist1 = (TH1F*)fileNoRPCUpdated->Get(hName.c_str());
    hist2 = (TH1F*)fileRPCUpdated->Get(hName.c_str());
    plot_normal_histograms( hist1, 
                            hist2, 
                            "fakeRate_EventWheelStationTP_matchedRPCUpdated", 
                            "", 
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