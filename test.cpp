#include "DTNtupleTPGSimAnalyzer.h"

void test() {

    // Open ROOT files
    std::string inputDir = "output/";
    std::string fileName = "DTNtupleTPGSimAnalyzer_Efficiency.root";

    TFile *fileNoRPC          = TFile::Open((inputDir+"noRPC/"+fileName).c_str());
    TFile *fileRPC            = TFile::Open((inputDir+"RPC/"+fileName).c_str());
    TFile *fileNoRPCUpdated   = TFile::Open((inputDir+"noRPCUpdated/"+fileName).c_str());
    TFile *fileRPCUpdated     = TFile::Open((inputDir+"RPCUpdated/"+fileName).c_str());
    TFile *fileRPCOnly        = TFile::Open((inputDir+"RPCOnly/"+fileName).c_str());
    TFile *fileRPCOnlyUpdated = TFile::Open((inputDir+"RPCOnlyUpdated/"+fileName).c_str());


    std::string saveDir = "--";
    
    // // ------------------------------------------------------------------------------
    // // INPUT FILES
    // // ------------------------------------------------------------------------------
    // std::string inputDir = "input/";
    // std::map<std::string,std::string> m_files;
    // // m_files["noRPC"]        = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_step2_noRPC.root";
    // // m_files["RPC"]          = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_step2_RPC.root";
    // // m_files["RPCUpdated"]   = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_withRPC_PHASE2_TN_33BX.root";
    // // m_files["noRPCUpdated"] = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_noRPC_PHASE2_TN_33BX.root";
    // m_files["RPCOnly"]         = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_Dec2025.root";
    // m_files["RPCOnlyUpdated"]  = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_RPCPhase2_RPCOnlyFlag.root";
    // m_files["test"]            = "test.root"; // It is a copy of m_files["RPC"]

    // if (!fileNoRPC || !fileRPC) {
    //     std::cout << "Error: Could not open one or both files!" << std::endl;
    //     return;
    // }

    std::vector<std::string> algoTag  = {"AM", "AM+RPC"};
    // std::vector<std::string> totalTag = {"matched", "total"};
    std::vector<std::string> chambTag = {"MB1", "MB2", "MB3", "MB4"};
    std::vector<std::string> wheelTag = {"Wh.-2","Wh.-1","Wh.0","Wh.+1","Wh.+2",};
    std::vector<std::string> secTags   = { "Sec1", "Sec2", "Sec3", "Sec4", "Sec5", "Sec6", "Sec7", "Sec8","Sec9","Sec10","Sec11","Sec12"};

    // std::vector<std::string> effDir = {
    //                                    "output/noRPC/histograms/effPlots/",
    //                                    "output/RPC/histograms/effPlots/",
    //                                    "output/noRPCUpdated/histograms/effPlots/", 
    //                                    "output/RPCUpdated/histograms/effPlots/",
    //                                 };

    TH1F *hTotal;
    TH1F *hMatched;
    std::string hName = "";
    std::vector<std::string> v_plot;

    std::cout << "--------------------------------" << std::endl;
    std::cout << "DT AM and DT + RPC  Studies" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    v_plot.clear();                                
    v_plot.push_back("EffEtaGenSeg");
    v_plot.push_back("EffEtaGenSeg20");
    v_plot.push_back("Eff_TPwheels");
    // v_plot.push_back("Eff_TPnotMatched");
    
    // for (int i = 0; i < 4; ++i){
    //     for (const auto & algo : algoTag){
    //         int chamberNumber = i+1;
    //         v_plot.push_back("hEff_MB" + std::to_string(chamberNumber) + "_"+algo);
    //     }
    // }

    // for (const auto& plot : v_plot) {
    //     hName = plot;
    //     hTotal =   (TH1F*)fileNoRPC->Get((hName+"_total").c_str());
    //     hMatched = (TH1F*)fileNoRPC->Get((hName+"_matched").c_str());
    //     plot_eff( hName, hMatched, hTotal, effDir[0]);
    //     hTotal =   (TH1F*)fileRPC->Get((hName+"_total").c_str());
    //     hMatched = (TH1F*)fileRPC->Get((hName+"_matched").c_str());
    //     plot_eff( hName, hMatched, hTotal, effDir[1]);
    // }

    // -------------------------------------------
    // For comparison plots
    // -------------------------------------------
    // std::string saveDir = "output/histogram_comparison/";

    saveDir = "plots/DT+RPC_vs_DT/efficiency/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) {
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    
    // ---------------
    // eff plots
    v_plot.clear();
    v_plot.push_back("Eff_TPwheels");
    v_plot.push_back("fakeRate_WheelStationTP");
    v_plot.push_back("fakeRate_TPnot");
    
    
    // for (const auto & secTag : secTags){
    //     hName = "Eff_TPwheels_"+secTag;
    //     v_plot.push_back(hName);
    // }
    // for (const auto & secTag : secTags){
    //     hName = "fakeRateTP_WheelvsStation_"+secTag;
    //     v_plot.push_back(hName);
    // }

    TH1F *hTotal1;
    TH1F *hMatched1;
    TH1F *hTotal2;
    TH1F *hMatched2;

    hMatched1 = (TH1F*)fileNoRPC->Get("Eff_TPwheels_matched");
    hTotal1 =   (TH1F*)fileNoRPC->Get("Eff_TPwheels_total");

    plotEffWheelStation("Eff_TPwheels",  // histogram name
                        hMatched1, // histogram passed
                        hTotal1, // histogram total
                        saveDir, // directory to save
                        "DT AM" ); // Legend

    return;

    for (const auto& plot : v_plot) {
        // hName = plot;
        TH1F *hTotal1 =   (TH1F*)fileNoRPC->Get((plot+"_total").c_str());
        TH1F *hMatched1 = (TH1F*)fileNoRPC->Get((plot+"_matched").c_str());
        TH1F *hTotal2 =   (TH1F*)fileRPC->Get((plot+"_total").c_str());
        TH1F *hMatched2 = (TH1F*)fileRPC->Get((plot+"_matched").c_str());
        plot_eff_fake_rate( plot, hMatched1, hTotal1, hMatched2, hTotal2, "DT AM", saveDir);
    }

   
    // ---------------
    // Normal plot
    saveDir = "plots//DT+RPC_vs_DT/variables/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) {
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }
    v_plot.clear();
    v_plot.push_back("hNSeg");
    v_plot.push_back("hNTrigs");
    v_plot.push_back("hRatioNtpNseg_total");
    v_plot.push_back("TPnotMatched");
    v_plot.push_back("TPMatched");
    v_plot.push_back("hTrigFlag");
    v_plot.push_back("hTPMatchedRPCflag");
    v_plot.push_back("BX_forFakeRate");
    v_plot.push_back("RPCFlag_forFakeRate");
    v_plot.push_back("fakeRate_EventWheelStationTP_matched");

    // for (const auto & secTag : secTags){
    //     hName = "fakeRate_EventWheelStationTP_"+secTag+"_matched";
    //     v_plot.push_back(hName);
    // }

    for (const auto& plot : v_plot) {
        // hName = "hNSeg";
        TH1F *hist1 = (TH1F*)fileNoRPC->Get(plot.c_str());
        TH1F *hist2 = (TH1F*)fileRPC->Get(plot.c_str());
        plot_normal_histograms( hist1, 
                                hist2, 
                                plot, 
                                "", 
                                "DT AM",
                                saveDir, 
                                false);
    }
    
    // ----Time of the TPs associated with prompt muons [ns]-----
    saveDir = "plots//DT+RPC_vs_DT/time/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) {
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    for (const auto & wheel : wheelTag) {
        for (const auto & chamb : chambTag) {
            // ---------------------------  
            // t0
            std::string hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";
            TH1F *hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
            TH1F *hist2 = (TH1F*)fileRPC->Get(hName.c_str());
            
            std::string wheel2 = wheel;
            wheel2 = wheel2.erase(1, 2);  // Removes "W.": "Wh.-2"→ "W-2"
            
            plot_t0_histograms( hist1, hist2, hName, 
                "Time of the TPs associated with prompt muons [ns]", 
                (wheel2+" "+chamb).c_str(),
                "DT AM",
                saveDir, 
                true);
            // ---------------------------    
            // BX
            hName = "hPh2TpgPhiEmuAmBX"+wheel+chamb+"_matched";
            hist1 = (TH1F*)fileNoRPC->Get(hName.c_str());
            hist2 = (TH1F*)fileRPC->Get(hName.c_str());

            plot_BX_histograms( hist1, hist2, hName, 
                "BX of the TPs associated with prompt muons [ns]", 
                (wheel2+" "+chamb).c_str(),
                "DT AM",
                saveDir, 
                false);
        }
    }

    
    TH1F *hist1;
    TH1F *hist2;
    TH1F *hist3;
    
    std::cout << "--------------------------------" << std::endl;
    std::cout << "DT AM and DT + RPC time phase2 Studies" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    // saveDir = "output/histogram_comparison_RPCUpdate/";
    saveDir = "plots/DT+RPCupdated_vs_DTupdated/efficiency/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }
    
    v_plot.clear();
    v_plot.push_back("Eff_TPwheels");
    v_plot.push_back("fakeRate_WheelStationTP");
    v_plot.push_back("fakeRate_TPnot");
    v_plot.push_back("Eff_TPnotMatched");
    
    for (const auto& plot : v_plot) {
        // hName = plot;
        TH1F *hTotal1 =   (TH1F*)fileNoRPCUpdated->Get((plot+"_total").c_str());
        TH1F *hMatched1 = (TH1F*)fileNoRPCUpdated->Get((plot+"_matched").c_str());
        TH1F *hTotal2 =   (TH1F*)fileRPCUpdated->Get((plot+"_total").c_str());
        TH1F *hMatched2 = (TH1F*)fileRPCUpdated->Get((plot+"_matched").c_str());
        plot_eff_fake_rate( plot, hMatched1, hTotal1, hMatched2, hTotal2, "DT AM", saveDir);
    }
    

    saveDir = "plots/DT+RPCupdated_vs_DTupdated/variables/";

    v_plot.clear();
    v_plot.push_back("hNSeg");
    v_plot.push_back("hNTrigs");
    v_plot.push_back("hRatioNtpNseg_total");
    v_plot.push_back("TPnotMatched");
    v_plot.push_back("TPMatched");
    v_plot.push_back("hTrigFlag");
    v_plot.push_back("hTPMatchedRPCflag");
    v_plot.push_back("BX_forFakeRate");
    v_plot.push_back("RPCFlag_forFakeRate");
    v_plot.push_back("fakeRate_EventWheelStationTP_matched");
    
    // for (const auto & secTag : secTags){
        //     hName = "fakeRate_EventWheelStationTP_"+secTag+"_matched";
        //     v_plot.push_back(hName);
        // }
        
    for (const auto& plot : v_plot) {
        // hName = "hNSeg";
        TH1F *hist1 = (TH1F*)fileNoRPCUpdated->Get(plot.c_str());
        TH1F *hist2 = (TH1F*)fileRPCUpdated->Get(plot.c_str());
        plot_normal_histograms( hist1, hist2, plot, 
                                "", 
                                "DT AM",
                                saveDir, 
                                false);
    }

    
    
    // -------------------------------------------------------------------------------
    // Comparision with RPC only segments
    std::cout << "--------------------------------" << std::endl;
    std::cout << "RPC Only Studies" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    // saveDir = "output/histogram_RPCOnly_comparison/";
    saveDir = "plots/DT+RPC_vs_RPConly/efficiency/"; 
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    // eff plots
    v_plot.clear();
    v_plot.push_back("Eff_TPRPC_wheels");
    

    // for (const auto& plot : v_plot) {
    //     // hName = plot;
    //     TH1F *hTotal1 =   (TH1F*)fileRPCOnly->Get((plot+"_total").c_str());
    //     if (!hTotal1) std::cerr << "Error: Could not retrieve " << plot+"_total" << " !!!!!!" << std::endl;
    //     TH1F *hMatched1 = (TH1F*)fileRPCOnly->Get((plot+"_matched").c_str());
    //     if (!hMatched1) std::cerr << "Error: Could not retrieve " << plot+"_matched" << " !!!!!!" << std::endl;
    //     TH1F *hTotal2 =   (TH1F*)fileRPC->Get((plot+"_total").c_str());
    //     if (!hTotal2) std::cerr << "Error: Could not retrieve " << plot+"_total" << " !!!!!!" << std::endl;
    //     TH1F *hMatched2 = (TH1F*)fileRPC->Get((plot+"_matched").c_str());
    //     if (!hMatched2) std::cerr << "Error: Could not retrieve " << plot+"_matched" << " !!!!!!" << std::endl;

    //     plot_eff_fake_rate( plot, hMatched1, hTotal1, hMatched2, hTotal2, "RPC Only", saveDir);

    // }
    
    hName = "Eff_TPRPC_wheels";
    // hName = "Eff_TPwheels";  // Using DT normal efficiency
    hTotal1 =   (TH1F*)fileRPCOnly->Get((hName+"_total").c_str());
    if (!hTotal1) std::cerr << "Error: Could not retrieve " << hName+"_total" << " !!!!!!" << std::endl;
    hMatched1 = (TH1F*)fileRPCOnly->Get((hName+"_matched").c_str());
    if (!hMatched1) std::cerr << "Error: Could not retrieve " << hName+"_total" << " !!!!!!" << std::endl;
    
    hName = "Eff_TPwheels";
    hTotal2 =   (TH1F*)fileRPC->Get((hName+"_total").c_str());
    if (!hTotal2) std::cerr << "Error: Could not retrieve " << hName+"_total" << " !!!!!!" << std::endl;
    hMatched2 = (TH1F*)fileRPC->Get((hName+"_matched").c_str());
    if (!hMatched2) std::cerr << "Error: Could not retrieve " << hName+"_total" << " !!!!!!" << std::endl;
    
    plot_eff_fake_rate( hName, hMatched1, hTotal1, hMatched2, hTotal2, "RPC Only", saveDir);
    

    saveDir = "plots/DT+RPC_vs_RPConly/variables/";
    v_plot.clear();
    v_plot.push_back("hNTrigs");
    v_plot.push_back("hTrigFlag");
    v_plot.push_back("hTPMatchedRPCflag");
    
        
    for (const auto& plot : v_plot) {
        // hName = "hNSeg";
        TH1F *hist1 = (TH1F*)fileNoRPC->Get(plot.c_str());
        TH1F *hist2 = (TH1F*)fileRPC->Get(plot.c_str());
        plot_normal_histograms( hist1, hist2, plot, 
                                "", 
                                "RPC Only",
                                saveDir, 
                                false);
    }

    // ----------------------------------------------------------
    // ----Time of the TPs associated with prompt muons [ns]-----
    // ----------------------------------------------------------
    // saveDir = "output/t0RPCOnly/";
    saveDir = "plots/DT+RPC_vs_RPConly/time/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) {
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    for (const auto & wheel : wheelTag) {
        for (const auto & chamb : chambTag) {
            std::string wheel2 = wheel;
            wheel2 = wheel2.erase(1, 2);  // Removes "W.": "Wh.-2"→ "W-2"
            
            // ---------------------------  
            // t0
            std::string hName = "hTPRPCOnlygT0"+wheel+chamb+"_matched";
            TH1F *hist1 = (TH1F*)fileRPCOnly->Get(hName.c_str());
            if (!hist1) std::cerr << "Error: Could not retrieve " << hName << " !!!!!!" << std::endl;

            hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";
            TH1F *hist2 = (TH1F*)fileRPC->Get(hName.c_str());
            if (!hist2) std::cerr << "Error: Could not retrieve " << hName << " !!!!!!" << std::endl;
            
            plot_t0_histograms( hist1, hist2, hName, 
                                "Time of the TPs associated with prompt muons [ns]", 
                                (wheel2+" "+chamb).c_str(),
                                "RPC only",
                                saveDir, 
                                true);

            // ---------------------------  
            // BX
            hName = "hPh2TpgPhiEmuAmBX"+wheel+chamb+"_matched";
            hist1 = (TH1F*)fileRPCOnly->Get(hName.c_str());
            hist2 = (TH1F*)fileRPC->Get(hName.c_str());
            if (!hist1 || !hist2) std::cerr << "Error: Could not retrieve " << hName << " !!!!!!" << std::endl;

            plot_BX_histograms( hist1, hist2, hName, 
                                "BX of the TPs associated with prompt muons [ns]", 
                                (wheel2+" "+chamb).c_str(),
                                "RPC Only",
                                saveDir, 
                                false);
            
        }
    }

    std::cout << "--------------------------------" << std::endl;
    std::cout << "RPC Only Updated Studies" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    // saveDir = "output/histogram_RPCOnlyUpdated_comparison/";
    saveDir = "plots/DT+RPC_vs_RPConlyUpdated/efficiency/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    //  -------------------- OLD --------------------------------------

    hName = "Eff_TPRPC_wheels";
    // hName = "Eff_TPwheels";  // Using DT normal efficiency
    hTotal1 =   (TH1F*)fileRPCOnlyUpdated->Get((hName+"_total").c_str());
    if (!hTotal1) std::cerr << "Error: Could not retrieve " << hName+"_total" << " !!!!!!" << std::endl;
    hMatched1 = (TH1F*)fileRPCOnlyUpdated->Get((hName+"_matched").c_str());
    if (!hMatched1) std::cerr << "Error: Could not retrieve " << hName+"_total" << " !!!!!!" << std::endl;

    hName = "Eff_TPwheels";
    hTotal2 =   (TH1F*)fileRPC->Get((hName+"_total").c_str());
    if (!hTotal2) std::cerr << "Error: Could not retrieve " << hName+"_total" << " !!!!!!" << std::endl;
    hMatched2 = (TH1F*)fileRPC->Get((hName+"_matched").c_str());
    if (!hMatched2) std::cerr << "Error: Could not retrieve " << hName+"_total" << " !!!!!!" << std::endl;

    plot_eff_fake_rate( hName, hMatched1, hTotal1, hMatched2, hTotal2, "RPC Only Updated", saveDir);
    
    // ----------------------------------------------------------
    // ----Time of the TPs associated with prompt muons [ns]-----
    // ----------------------------------------------------------
    // saveDir = "output/t0RPCOnlyUpdated/";
    saveDir = "plots/DT+RPC_vs_RPConlyUpdated/time/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) {
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    for (const auto & wheel : wheelTag) {
        for (const auto & chamb : chambTag) {
            
            std::string hName = "";
            hName = "hTPRPCOnlygT0"+wheel+chamb+"_matched";
            hist1 = (TH1F*)fileRPCOnlyUpdated->Get(hName.c_str());
            if (!hist1) std::cerr << "Error: Could not retrieve " << hName << " !!!!!!" << std::endl;
            hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";
            hist2 = (TH1F*)fileRPC->Get(hName.c_str());
            if (!hist2) std::cerr << "Error: Could not retrieve " << hName << " !!!!!!" << std::endl;

            std::string wheel2 = wheel;
            wheel2 = wheel2.erase(1, 2);  // Removes "h.": "Wh.-2"→ "W-2"

            plot_t0_histograms( hist1, hist2,
                                "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched",
                                "Time of the TPs associated with prompt muons [ns]",
                                (wheel2+" "+chamb).c_str(),
                                "RPC Only Updated",
                                saveDir,
                                true);

        }
    }

    std::cout << "--------------------------------" << std::endl;
    std::cout << "END PROGRAM" << std::endl;
    std::cout << "--------------------------------" << std::endl;

}