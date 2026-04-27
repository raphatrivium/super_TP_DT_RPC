#include "DTNtupleTPGSimAnalyzer.h"

void plot_histograms() { 

    // Open ROOT files
    std::string inputDir = "output/";
    std::string fileName = "DTNtupleTPGSimAnalyzer_Efficiency.root";

    TFile *fileDTAM           = TFile::Open((inputDir+"DTAM/"+fileName).c_str());
    TFile *fileRPC            = TFile::Open((inputDir+"RPC/"+fileName).c_str());
    TFile *fileRPCcorrected   = TFile::Open((inputDir+"RPCcorrected/"+fileName).c_str());
    TFile *fileRPC_Flag01     = TFile::Open((inputDir+"RPC_Flag0and1/"+fileName).c_str());
    TFile *fileRPC_Flag1      = TFile::Open((inputDir+"RPC_Flag1/"+fileName).c_str());
    TFile *fileRPC_Flag2      = TFile::Open((inputDir+"RPC_Flag2/"+fileName).c_str());
    TFile *fileDTAMUpdated    = TFile::Open((inputDir+"DTAMUpdated/"+fileName).c_str());
    TFile *fileRPCUpdated     = TFile::Open((inputDir+"RPCUpdated/"+fileName).c_str());
    TFile *fileDTRPCOnly      = TFile::Open((inputDir+"DTRPCOnly/"+fileName).c_str());
    TFile *fileRPCOnly        = TFile::Open((inputDir+"RPCOnly/"+fileName).c_str());
    TFile *fileRPCOnlyUpdated = TFile::Open((inputDir+"RPCOnlyUpdated/"+fileName).c_str());
    
    TFile *fileDTAMv23         = TFile::Open((inputDir+"DTAMv2.3/"+fileName).c_str());
    TFile *fileRPCv23          = TFile::Open((inputDir+"RPCv2.3/"+fileName).c_str());
    TFile *fileRPCcorrectedv23 = TFile::Open((inputDir+"RPCcorrected2.3/"+fileName).c_str());
    TFile *fileRPCOnlyv23      = TFile::Open((inputDir+"RPCOnlyv2.3/"+fileName).c_str());
    TFile *fileRPCOnlyUpdatedv23      = TFile::Open((inputDir+"RPCOnlyUpdatedv2.3/"+fileName).c_str());

    

    std::string saveDir = "--";
    
    std::vector<std::string> algoTag  = {"AM", "AM+RPC"};
    // std::vector<std::string> totalTag = {"matched", "total"};
    std::vector<std::string> chambTag = {"MB1", "MB2", "MB3", "MB4"};
    std::vector<std::string> wheelTag = {"Wh.-2","Wh.-1","Wh.0","Wh.+1","Wh.+2",};
    std::vector<std::string> secTags   = { "Sec1", "Sec2", "Sec3", "Sec4", "Sec5", "Sec6", "Sec7", "Sec8","Sec9","Sec10","Sec11","Sec12"};

    // --------------------------------
    // DT AM and DT + RPC  Studies" 
    // --------------------------------
    std::cout << "----------- DT AM and DT + RPC  Studies -----------" << std::endl;
   
    // ---------------
    // eff plots
    // ---------------
    saveDir = "plots/DT+RPC_vs_DT/efficiency/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) {
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    // For 1 histogram
    // plotEffWheelStation("Eff_TPwheels", fileDTAM, "DT AM", kRed, saveDir  );

    // For 2 histogram
    // plotEffWheelStation("Eff_TPwheels", fileDTAM, "DT AM", kRed ,fileRPC, "DT AM + RPC", kBlue, saveDir );
    // plotEffWheelStation("fakeRate_WheelStationTP", fileDTAM, "DT AM", kRed ,fileRPC, "DT AM + RPC", kBlue, saveDir );
    // plotEffWheelStation("fakeRate_TP", fileDTAM, "DT AM", kRed ,fileRPC, "DT AM + RPC", kBlue, saveDir );
    // for (const auto & secTag : secTags){
    //     plotEffWheelStation("Eff_TPwheels_"+secTag, fileDTAM, "DT AM", kRed ,fileRPC, "DT AM + RPC", kBlue, saveDir );
    // }
    // for (const auto & secTag : secTags){
    //     plotEffWheelStation("fakeRateTP_WheelvsStation_"+secTag, fileDTAM, "DT AM", kRed ,fileRPC, "DT AM + RPC", kBlue, saveDir );
    // }

    // ---------------
    // Other variables
    // ---------------
    saveDir = "plots/DT+RPC_vs_DT/variables/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) {
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    // plot_histo("hNSeg", fileDTAM, "DT AM", kRed ,fileRPC, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("hNTrigs", fileDTAM, "DT AM", kRed ,fileRPC, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("hRatioNtpNseg_total", fileDTAM, "DT AM", kRed ,fileRPC, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("hTrigFlag", fileDTAM, "DT AM", kRed ,fileRPC, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("TPMatched", fileDTAM, "DT AM", kRed ,fileRPC, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("hTPMatchedRPCflag", fileDTAM, "DT AM", kRed ,fileRPC, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("BX_forFakeRate", fileDTAM, "DT AM", kRed ,fileRPC, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("RPCFlag_forFakeRate", fileDTAM, "DT AM", kRed ,fileRPC, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("fakeRate_EventWheelStationTP_matched", fileDTAM, "DT AM", kRed ,fileRPC, "DT AM + RPC", kBlue, saveDir);

    // --------------------
    // Time of the TPs 
    // --------------------
    saveDir = "plots/DT+RPC_vs_DT/time/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) {
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    // for (const auto & wheel : wheelTag) {
    //     std::string wh = wheel;  
    //     wh = wh.erase(1, 2); // Removes "h.": "Wh.-2"→ "W-2"
    //     for (const auto & chamb : chambTag) {
    //         std::string hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";
    //         plot_t0_histo( hName, fileDTAM, "DT AM", kRed, fileRPC, "DT AM + RPC", kBlue, (wh+" "+chamb), saveDir, true);
    //         // TODO
    //         //plot_BX_histo( hName, fileDTAM, "DT AM", kRed, fileRPC, "DT AM + RPC", kBlue, (wh+" "+chamb), saveDir, true);
    //     }
    // }

    
    // --------------------------------
    // Comparison between AM 2.0 (CMSSW 14) and AM 2.3 (CMSSW 15)
    // --------------------------------
    saveDir = "plots/Comparison_AM2.0_AM2.3/efficiency/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    plotEffWheelStation("Eff_TPwheels",
                        {fileDTAM, fileRPC, fileDTAMv23, fileRPCv23},
                        {"DT AM", "DT AM + RPC", "DT AMv2.3", "DT AMv2.3 + RPC"},
                        {{kRed, 1}, {kBlue, 1}, {kRed, 22}, {kBlue, 33}},
                        saveDir ) ;

    // --------------------------------
    saveDir = "plots/Comparison_AM2.0_AM2.3/variables/";
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    plot_histo("hNTrigs",
                {fileDTAM, fileRPC, fileDTAMv23, fileRPCv23},
                {"DT AM", "DT AM + RPC", "DT AMv2.3", "DT AMv2.3 + RPC"},
                {{kRed, 1}, {kBlue, 1}, {kRed, 2}, {kBlue, 2}},
                saveDir, 
                false);

    // --------------------------------
    saveDir = "plots/Comparison_AM2.0_AM2.3/time/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) {
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    
    for (const auto & wheel : wheelTag) {
        std::string wh = wheel;  
        wh = wh.erase(1, 2); // Removes "h.": "Wh.-2"→ "W-2"
        for (const auto & chamb : chambTag) {
            std::string hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";
            plot_t0_histo( hName,
                            {fileDTAM, fileRPC, fileDTAMv23, fileRPCv23},
                            {"DT AM 2.0", "DT AMv2.0 + RPC", "DT AMv2.3", "DT AMv2.3 + RPC"},
                            {{kRed, 1}, {kBlue, 1}, {kRed, 2}, {kBlue, 2}},
                            (wh+" "+chamb), 
                            saveDir, 
                            true);
            // TODO
            //plot_BX_histo( hName, fileDTAM, "DT AM", kRed, fileRPC, "DT AM + RPC", kBlue, (wh+" "+chamb), saveDir, true);
        }
    }
    

    // --------------------------------
    // Comparison RPC correction (2 layers time combination)
    // --------------------------------
    saveDir = "plots/RPC_Corrected/efficiency/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    plotEffWheelStationMB1MB2("Eff_TPwheels",
                                {fileDTAMv23, fileRPCv23, fileRPCcorrectedv23},
                                {"DT AM", "DT AM + RPC", "DT+RPC Corrected"},
                                {{kRed, 20}, {kBlue, 21}, {kYellow+2, 33}},
                                saveDir ) ;

    // --------------------------------
    saveDir = "plots/RPC_Corrected/variables/";
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    plot_histo("hNTrigs",
                {fileDTAMv23, fileRPCv23, fileRPCcorrectedv23},
                {"DT AM", "DT AM + RPC", "DT+RPC Corrected"},
                {{kRed, 1}, {kBlue, 1}, {kYellow+2, 1}},
                saveDir, 
                false);

    // --------------------------------
    saveDir = "plots/RPC_Corrected/time/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    for (const auto & wheel : wheelTag) {
        std::string wh = wheel;  
        wh = wh.erase(1, 2); // Removes "h.": "Wh.-2"→ "W-2"
        for (const auto & chamb : chambTag) {
            std::string hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";
            plot_t0_histo( hName,
                            {fileDTAMv23, fileRPCv23, fileRPCcorrectedv23},
                            {"DT AM", "DT AM + RPC", "DT+RPC Corrected"},
                            {{kRed, 1}, {kBlue, 1}, {kYellow+2, 1}},
                            (wh+" "+chamb), 
                            saveDir, 
                            true);
            // TODO
            //plot_BX_histo( hName, fileDTAM, "DT AM", kRed, fileRPC, "DT AM + RPC", kBlue, (wh+" "+chamb), saveDir, true);
        }
    }

    // --------------------------------
    // RPC Efficiency SimLinks
    // --------------------------------
    saveDir = "plots/RPC_Efficiency/efficiency/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    plotEffWheelStationMB1MB2("Eff_TPwheels",
                                {fileDTAMv23, fileRPCv23, fileRPCOnlyv23},
                                {"DT AM", "DT AM + RPC", "RPC Only"},
                                {{kRed, 20}, {kBlue, 21}, {kGreen+2, 22}},
                                saveDir ) ;

    // --------------------------------
    saveDir = "plots/RPC_Efficiency/variables/";
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    plot_histo("hNTrigs",
                {fileDTAMv23, fileRPCv23, fileRPCcorrectedv23, fileRPCOnlyv23},
                {"DT AM", "DT AM + RPC", "DT+RPC Corrected", "RPC Only"},
                {{kRed, 1}, {kBlue, 1}, {kYellow+2, 1}, {kGreen+2, 1}},
                saveDir, 
                false);

    // --------------------------------
    saveDir = "plots/RPC_Efficiency/time/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    for (const auto & wheel : wheelTag) {
        std::string wh = wheel;  
        wh = wh.erase(1, 2); // Removes "h.": "Wh.-2"→ "W-2"
        for (const auto & chamb : chambTag) {
            std::string hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";
            plot_t0_histo(  hName,
                            {fileDTAMv23, fileRPCv23, fileRPCcorrectedv23, fileRPCOnlyv23},
                            {"DT AM", "DT AM + RPC", "DT+RPC Corrected", "RPC Only"},
                            {{kRed, 1}, {kBlue, 1}, {kYellow+2, 1}, {kGreen+2, 1}},
                            (wh+" "+chamb), 
                            saveDir, 
                            true);
            // TODO
            //plot_BX_histo( hName, fileDTAM, "DT AM", kRed, fileRPC, "DT AM + RPC", kBlue, (wh+" "+chamb), saveDir, true);
        }
    }

    // --------------------------------
    // RPC Phase 2 time
    // --------------------------------
    saveDir = "plots/RPC_Phase_2/efficiency/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    plotEffWheelStationMB1MB2("Eff_TPwheels",
                                {fileDTAMv23, fileRPCv23, fileRPCOnlyv23, fileRPCOnlyUpdatedv23},
                                {"DT AM", "DT AM + RPC", "RPC Only", "RPC Only Phase 2"},
                                {{kRed, 20}, {kBlue, 21}, {kGreen+2, 22}, {kOrange+1, 22}}, 
                                saveDir ) ;

    // --------------------------------
    saveDir = "plots/RPC_Phase_2/variables/";
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    plot_histo("hNTrigs",
                {fileDTAMv23, fileRPCv23, fileRPCcorrectedv23, fileRPCOnlyv23, fileRPCOnlyUpdatedv23},
                {"DT AM", "DT AM + RPC", "DT+RPC Corrected", "RPC Only", "RPC Only Phase 2"},
                {{kRed, 1}, {kBlue, 1}, {kYellow+2, 1}, {kGreen+2, 1}, {kOrange+1, 1}},
                saveDir, 
                false);

    // --------------------------------
    saveDir = "plots/RPC_Phase_2/time/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    for (const auto & wheel : wheelTag) {
        std::string wh = wheel;  
        wh = wh.erase(1, 2); // Removes "h.": "Wh.-2"→ "W-2"
        for (const auto & chamb : chambTag) {
            std::string hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";
            plot_t0_histo(  hName,
                            {fileDTAMv23, fileRPCv23, fileRPCcorrectedv23, fileRPCOnlyv23, fileRPCOnlyUpdatedv23},
                            {"DT AM", "DT AM + RPC", "DT+RPC Corrected", "RPC Only", "RPC Only Phase 2"},
                            {{kRed, 1}, {kBlue, 1}, {kYellow+2, 1}, {kGreen+2, 1}, {kOrange+1, 1}},
                            (wh+" "+chamb), 
                            saveDir, 
                            true);
            // TODO
            //plot_BX_histo( hName, fileDTAM, "DT AM", kRed, fileRPC, "DT AM + RPC", kBlue, (wh+" "+chamb), saveDir, true);
        }
    }

    return;

    // --------------------------------
    // DT AM and DT + RPC time phase2 Studies" 
    // --------------------------------
    std::cout << "--------------------------------" << std::endl;
    std::cout << "DT AM and DT + RPC time phase2 Studies" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    // ---------------
    // eff plots
    // ---------------
    saveDir = "plots/DT+RPCupdated_vs_DTupdated/efficiency/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }
    
    // plotEffWheelStation("Eff_TPwheels", fileDTAMUpdated, "DT AM Updated", kRed ,fileRPCUpdated, "DT AM + RPC Updated", kBlue, saveDir );
    // plotEffWheelStation("fakeRate_WheelStationTP", fileDTAMUpdated, "DT AM Updated", kRed ,fileRPCUpdated, "DT AM + RPC Updated", kBlue, saveDir );
    // plotEffWheelStation("fakeRate_TP", fileDTAMUpdated, "DT AM Updated", kRed ,fileRPCUpdated, "DT AM + RPC Updated", kBlue, saveDir );
    // plotEffWheelStation("Eff_TPnotMatched", fileDTAMUpdated, "DT AM Updated", kRed ,fileRPCUpdated, "DT AM + RPC Updated", kBlue, saveDir );

    // ---------------
    // Other variables
    // ---------------
    saveDir = "plots/DT+RPCupdated_vs_DTupdated/variables/";
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    // plot_histo("hNTrigs", fileDTAMUpdated, "DT AM Updated", kRed ,fileRPCUpdated, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("TPnotMatched", fileDTAMUpdated, "DT AM Updated", kRed ,fileRPCUpdated, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("hRatioNtpNseg_total", fileDTAMUpdated, "DT AM Updated", kRed ,fileRPCUpdated, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("hTrigFlag", fileDTAMUpdated, "DT AM Updated", kRed ,fileRPCUpdated, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("TPMatched", fileDTAMUpdated, "DT AM Updated", kRed ,fileRPCUpdated, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("hTPMatchedRPCflag", fileDTAMUpdated, "DT AM Updated", kRed ,fileRPCUpdated, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("BX_forFakeRate", fileDTAMUpdated, "DT AM Updated", kRed ,fileRPCUpdated, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("RPCFlag_forFakeRate", fileDTAMUpdated, "DT AM Updated", kRed ,fileRPCUpdated, "DT AM + RPC", kBlue, saveDir);

    
    std::cout << "--------------------------------" << std::endl;
    std::cout << "RPC Only Studies" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    // ---------------
    // eff plots
    // ---------------
    saveDir = "plots/DT+RPC_vs_RPConly/efficiency/"; 
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    // plotEffWheelStation("Eff_TPwheels", fileRPCOnly, "RPConly", kGreen ,fileRPC, "DT AM + RPC Updated", kBlue, saveDir );
    // plotEffWheelStation("fakeRate_WheelStationTP", fileRPCOnly, "RPConly", kGreen ,fileRPC, "DT AM + RPC Updated", kBlue, saveDir );


    // ---------------
    // Other variables
    // ---------------
    saveDir = "plots/DT+RPC_vs_RPConly/variables/";
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }


    // plot_histo("hNTrigs", fileRPCOnly, "RPConly", kGreen ,fileRPC, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("hTrigFlag", fileRPCOnly, "RPConly", kGreen ,fileRPC, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("hTPMatchedRPCflag", fileRPCOnly, "RPConly", kGreen ,fileRPC, "DT AM + RPC", kBlue, saveDir);


    // ----------------------------------------------------------
    // Time of the TPs associated with prompt muons 
    // ----------------------------------------------------------
    saveDir = "plots/DT+RPC_vs_RPConly/time/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) {
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    // for (const auto & wheel : wheelTag) {
    //     std::string wh = wheel;  
    //     wh = wh.erase(1, 2); // Removes "h.": "Wh.-2"→ "W-2"
    //     for (const auto & chamb : chambTag) {
    //         std::string hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";
    //         plot_t0_histo( hName, fileRPCOnly, "RPConly", kGreen, fileRPC, "DT AM + RPC", kBlue, (wh+" "+chamb), saveDir, true);
    //         // TODO
    //         //plot_BX_histo( hName, fileDTAM, "DT AM", kRed, fileRPC, "DT AM + RPC", kBlue, (wh+" "+chamb), saveDir, true);
    //     }
    // }


    std::cout << "--------------------------------" << std::endl;
    std::cout << "RPC Only Updated Studies" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    // ---------------
    // eff plots
    // ---------------
    saveDir = "plots/DT+RPC_vs_RPConlyUpdated/efficiency/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    plotEffWheelStation("Eff_TPwheels",
                          {fileRPCOnly, fileRPCOnlyUpdated },
                          {"RPC Only", "RPC Only Phase2"},
                          {{kGreen, 22}, {kBlack, 23}},
                          saveDir ) ;

    plotEffWheelStationMB1MB2("Eff_TPwheels",
                          {fileRPCOnly, fileRPCOnlyUpdated },
                          {"RPC Only", "RPC Only Phase2"},
                          {{kGreen, 22}, {kBlack, 23}},
                          saveDir ) ;

    // plotEffWheelStation("fakeRate_WheelStationTP", 
    //                     fileRPCOnly, "RPC Only", kGreen, 
    //                     fileRPCOnlyUpdated, "RPC Only Updated", kBlack, saveDir );

    // plotEffWheelStation("Eff_TPwheels", 
    //                     fileRPCOnly, "RPC Only", {kGreen, 22}, 
    //                     fileRPC, "DT AM + RPC", {kBlue, 21}, 
    //                     fileRPCOnlyUpdated, "RPC Only Updated", {kBlack, 23},
    //                     saveDir );

    // plotEffWheelStationV2(  "Eff_TPwheels",
    //                         {fileRPC, fileRPCOnly},
    //                         {"DT AM + RPC", "RPC Only"},
    //                         {{kBlue, 21},{kGreen, 22}},
    //                         saveDir ) ;

    // plotEffWheelStationV2("Eff_TPwheels",
    //                       {fileRPC, fileRPCOnly, fileRPCOnlyUpdated, fileDTAM},
    //                       {"DT AM + RPC", "RPC Only", "RPC Only Updated", "DT AM"},
    //                       {{kBlue, 21},{kGreen, 22}, {kBlack, 23}, {kRed, 20}},
    //                       saveDir ) ;

    // plotEffWheelStationV2("Eff_TPwheels",
    //                       {fileDTAM, fileRPC, fileRPCOnly, fileRPCOnlyUpdated },
    //                       {"DT AM", "DT AM + RPC", "RPC Only", "RPC Only Phase2"},
    //                       {{kRed, 20}, {kBlue, 21}, {kGreen, 22}, {kBlack, 23}},
    //                       saveDir ) ;
    
    // -----------------------------------------------------
    // Time of the TPs associated with prompt muons
    // ------------------------------------------------------
    saveDir = "plots/DT+RPC_vs_RPConlyUpdated/time/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) {
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    // for (const auto & wheel : wheelTag) {
    //     std::string wh = wheel;  
    //     wh = wh.erase(1, 2); // Removes "h.": "Wh.-2"→ "W-2"
    //     for (const auto & chamb : chambTag) {
    //         std::string hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";
    //         plot_t0_histo( hName, fileRPCOnly, "RPConly", kGreen, fileRPCOnlyUpdated, "RPC Only Updated", kBlack, (wh+" "+chamb), saveDir, true);
    //         // TODO
    //         //plot_BX_histo( hName, fileDTAM, "DT AM", kRed, fileRPC, "DT AM + RPC", kBlue, (wh+" "+chamb), saveDir, true);
    //     }
    // }

    std::cout << "--------------------------------" << std::endl;
    std::cout << "Different Flags Studies" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    // ---------------
    // eff plots
    // ---------------
    saveDir = "plots/differentFlags/efficiency/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    // plotEffWheelStationV2("Eff_TPwheels",
    //                       {fileDTAM, fileRPC, fileRPC_Flag1, fileRPC_Flag2},
    //                       {"DT AM", "DT AM + RPC", "Flag 1", "Flag 2"},
    //                       {{kRed, 20}, {kBlue, 21}, {kGreen+2, 24}, {kBlack, 25}},
    //                       saveDir ) ;

    std::cout << "--------------------------------" << std::endl;
    std::cout << "All Studies" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    // ---------------------------------------------------------------------------
    //                            eff plots
    // ---------------------------------------------------------------------------
    saveDir = "plots/all/efficiency/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    // plotEffWheelStationV2("Eff_TPwheels",
    //                       {fileDTAM, fileRPC, fileRPCOnly, fileRPCOnlyUpdated, fileDTRPCOnly },
    //                       {"DT AM", "DT AM + RPC", "RPC Only", "RPC Only Phase2", "RPC Only (DT)"},
    //                       {{kRed, 20}, {kBlue, 21}, {kGreen+2, 22}, {kBlack, 23}, {kMagenta, 33}},
    //                       saveDir ) ;

    // plotEffWheelStationMB1MB2("Eff_TPwheels",
    //                             {fileDTAM, fileRPC, fileRPCOnly},
    //                             {"DT AM", "DT AM + RPC", "RPC Only"},
    //                             {{kRed, 20}, {kBlue, 21}, {kGreen+2, 22}},
    //                             saveDir ) ;

    

    


                                
    
    // plotEffWheelStationMB1MB2("Eff_TPwheels",
    //                             {fileRPCOnly},
    //                             {"RPC Only"},
    //                             {{kGreen+2, 22}},
    //                             saveDir ) ;

    plotEffWheelStationMB1MB2("fakeRate_WheelStationTP",
                                {fileDTAM, fileRPC, fileRPCOnly},
                                {"DT AM", "DT AM + RPC", "RPC Only"},
                                {{kRed, 20}, {kBlue, 21}, {kGreen+2, 22}},
                                saveDir ) ;

    // plotEffWheelStationMB1MB2("Eff_TPwheels",
    //                         {fileDTAM, fileRPC, fileDTRPCOnly },
    //                         {"DT AM", "DT AM + RPC", "RPC Only (DT)"},
    //                         {{kRed, 20}, {kBlue, 21}, {kMagenta, 33}},
    //                         saveDir ) ;

    // ---------------------------------------------------------------------------
    //                            Other variables
    // ---------------------------------------------------------------------------
    saveDir = "plots/all/variables/";
    if (gSystem->AccessPathName(saveDir.c_str())) { 
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    plot_histo("hNTrigs",
                 {fileDTAM, fileRPC, fileRPCOnly},
                 {"DT AM", "DT AM + RPC", "RPC Only"},
                 {{kRed, 1}, {kBlue, 1}, {kGreen+2, 1}},
                 saveDir, 
                 false);

                 
    // plot_histo("hNTrigs",
    //             {fileDTAM, fileRPC_Flag1, fileRPCOnly},
    //             {"DT AM", "DT AM + RPC", "RPC Only"},
    //             {{kRed, 1}, {kBlue, 1}, {kGreen+2, 1}},
    //             saveDir, 
    //             false);             

    plot_histo("hTrigFlag",
                 {fileDTAM, fileRPC, fileRPCOnly},
                 {"DT AM", "DT AM + RPC", "RPC Only"},
                 {{kRed, 1}, {kBlue, 1}, {kGreen+2, 1}},
                 saveDir, 
                 false);
    
    // plot_histo("hTrigFlag",
    //              {fileDTAM, fileRPC_Flag1, fileRPCOnly},
    //              {"DT AM", "DT AM + RPC", "RPC Only"},
    //              {{kRed, 1}, {kBlue, 1}, {kGreen+2, 1}},
    //              saveDir, 
    //              false);
    
    // plot_histo("hTrigFlag",
    // {fileDTAM, fileRPC},
    // {"DT AM", "DT AM + RPC"},
    // {{kRed, 1}, {kBlue, 1}},
    // saveDir, 
    // false);

    // plot_histo("hT0Flag0",
    //              {fileRPC},
    //              {"DT AM"},
    //              {{kRed, 1}},
    //              saveDir, 
    //              false, true);
    
    plot_histo("hT0Flag0",
                 {fileDTAMv23},
                 {"DT AM"},
                 {{kRed, 1}},
                 saveDir, 
                 false, true);

    // plot_histo("hT0Flag1",
    //              {fileRPC},
    //              {"DT AM + RPC"},
    //              {{kBlue, 1}},
    //              saveDir, 
    //              false, true);

    plot_histo("hT0Flag1",
                 {fileRPCv23},
                 {"DT AM + RPC"},
                 {{kBlue, 1}},
                 saveDir, 
                 false, true);
    
    plot_histo("hT0Flag2",
                 {fileRPCOnly},
                 {"RPC Only"},
                 {{kGreen+2, 1}},
                 saveDir, 
                 false, true);


    // plot_histoV2("hTrigFlag", fileRPCOnly, "RPConly", kGreen ,fileRPC, "DT AM + RPC", kBlue, saveDir);
    // plot_histo("hTPMatchedRPCflag", fileRPCOnly, "RPConly", kGreen ,fileRPC, "DT AM + RPC", kBlue, saveDir);


    // ----------------------------------------------------------
    // Time of the TPs associated with prompt muons 
    // ----------------------------------------------------------
    saveDir = "plots/all/time/";
    // Create the directory if it doesn't exist
    if (gSystem->AccessPathName(saveDir.c_str())) {
        gSystem->mkdir(saveDir.c_str(), true); // true = recursive
    }

    // for (const auto & wheel : wheelTag) {
    //     std::string wh = wheel;  
    //     wh = wh.erase(1, 2); // Removes "h.": "Wh.-2"→ "W-2"
    //     for (const auto & chamb : chambTag) {
    //         std::string hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";
    //         plot_t0_histo( hName,
    //                         {fileDTAM, fileRPC, fileRPCOnly},
    //                         {"DT AM", "DT AM + RPC", "RPC Only"},
    //                         {{kRed, 1}, {kBlue, 1}, {kGreen+2, 1}},
    //                         (wh+" "+chamb), 
    //                         saveDir, 
    //                         true);
    //         // TODO
    //         //plot_BX_histo( hName, fileDTAM, "DT AM", kRed, fileRPC, "DT AM + RPC", kBlue, (wh+" "+chamb), saveDir, true);
    //     }
    // }

    // for (const auto & wheel : wheelTag) {
    //     std::string wh = wheel;  
    //     wh = wh.erase(1, 2); // Removes "h.": "Wh.-2"→ "W-2"
    //     for (const auto & chamb : chambTag) {
    //         std::string hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";
    //         plot_t0_histo( hName,
    //                         {fileDTAM, fileRPC_Flag1, fileRPCOnly},
    //                         {"DT AM", "DT AM + RPC", "RPC Only"},
    //                         {{kRed, 1}, {kBlue, 1}, {kGreen+2, 1}},
    //                         (wh+" "+chamb), 
    //                         saveDir, 
    //                         true);
    //         // TODO
    //         //plot_BX_histo( hName, fileDTAM, "DT AM", kRed, fileRPC, "DT AM + RPC", kBlue, (wh+" "+chamb), saveDir, true);
    //     }
    // }

    

 

    std::cout << "--------------------------------" << std::endl;
    std::cout << "END PROGRAM" << std::endl;
    std::cout << "--------------------------------" << std::endl;

}