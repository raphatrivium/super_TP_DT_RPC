// This code is a modificated version file to run locally of the DTNtupleTPGSimAnalyzer_Efficiency.cpp 
// that can be found in the github: 
// https://github.com/jaimeleonh/DTNtuples/blob/unifiedPerf/test/DTNtupleTPGSimAnalyzer_Efficiency.C


#include "DTNtupleTPGSimAnalyzer.h"

int test() {

    bool testFlag = false;   // false - true
    bool fdebug = true;

    bool plotHistograms = true; // false - true

    // flagRPCselection = 0  : all RPC Flags
    // flagRPCselection = 1  : RPC used to overwrite TP timing info (both t0 and BX)
    // flagRPCselection = 2  : RPC only segment
    // flagRPCselection = 3  : RPC single hit not associated to any DT segment
    // flagRPCselection = 10 : RPC Flag == 0 &&  RPC Flag == 1.   "RPC Flag == 0": segment that could not be matched to any RPC cluster

    int flagRPCselection = 0;

    bool booltest = false;

    // ------------------------------------------------------------------------------
    // INPUT FILES
    // ------------------------------------------------------------------------------
    std::string inputDir = "input/";
    std::map<std::string,std::string> m_files;
    // m_files["noRPC"]        = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_step2_noRPC.root";
    // m_files["RPC"]          = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_step2_RPC.root";
    // m_files["RPCUpdated"]   = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_withRPC_PHASE2_TN_33BX.root";
    // m_files["noRPCUpdated"] = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_noRPC_PHASE2_TN_33BX.root";
    m_files["RPCOnly"]         = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_Dec2025.root";
    m_files["RPCOnlyUpdated"]  = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_RPCPhase2_RPCOnlyFlag.root";
    m_files["test"]            = "test.root"; // It is a copy of m_files["RPC"]

    // ------------------------------------------------------------------------------
    // Check if the files are present.
    // ------------------------------------------------------------------------------
    bool allExist = true;
    for (const auto& pair : m_files) {
        const std::string& name = pair.first;
        const std::string& fname = pair.second;
       
        bool fileExist = checkFilesInDirectory (fname, inputDir);
        if (!fileExist) allExist = false; 
    }
    if (!allExist){
        std::cout << "\n Some of the files are missing !!!!!. Check the list above \n" <<std::endl;
        return 1;
    }
    
    // ------------------------------------------------------------------------------
    // Loop in the map of files
    // ------------------------------------------------------------------------------
    for (const auto& pair : m_files) {
                               
        const std::string& name = pair.first;
        const std::string& file_name = pair.second;

        if (testFlag){ if ( file_name != m_files["test"] ) continue; }
        else{ if ( file_name == m_files["test"] ) continue; }

        std::cout << "-------------------------------------------" <<std::endl;
        std::cout << "["+name+"]: "+inputDir+file_name+"\n" <<std::endl;
        // std::cout << "-------------------------------------------" <<std::endl;

        bool fileRPCflag = false;
        if ( name == "RPCOnly" ) fileRPCflag = true;
        else if ( name == "RPCOnlyUpdated" ) fileRPCflag = true;
        else if ( name == "RPCUpdated" ) fileRPCflag = true;
        else if ( name == "RPC" ) fileRPCflag = true;
        else if ( name == "test" ) fileRPCflag = true;

        BarrelGeo barGeo("barrel_geometry.txt");
        // if ( name == "RPCOnly" ) barGeo = barGeo("barrel_geometry.txt");
   
        // ---------------------------------------
        // Making Map of Histograms 
        // ---------------------------------------
        std::map<std::string, TH1*> m_plots;
        std::map<std::string, TH2*> m_plots2;
        // std::map<std::string, TEfficiency*> m_effs;

        std::vector<std::string> algoTag  = {"AM", "AM+RPC", "Ph1"};
        std::vector<std::string> totalTag = {"matched", "total"};
        std::vector<std::string> chambTag = {"MB1",     "MB2", "MB3", "MB4"};
        std::vector<std::string> wheelTag = {"Wh.-2","Wh.-1","Wh.0","Wh.+1","Wh.+2",};

        m_plots["hGenEta"] = new TH1D("hGenEta", "Gen Muon #eta distribution ; #eta; Entries", 200, -1.5, +1.5);
        m_plots["hGenPt"] = new TH1D("hGenPt", "Gen Muon pT distribution ; pT; Entries", 200, 0, 200);
        m_plots["hGenIdPDG"] = new TH1D("hGenIdPDG", "Gen PDG ID ; PDG ID; Entries", 40, -20, 20);

        // m_plots["EffEtaGenSeg_total"] = new TH1D("EffEtaGenSeg_total", "Muon Reconstruction Efficiency; #eta; Efficiency", 100, -2, 2);

        m_plots["hGenTPdeltaPhi"] = new TH1D("hGenTPdeltaPhi", "Delta Phi between Gen and TP ; Delta Phi; Entries", 600, 0, 0.5);

        m_plots["hTPStationDeltaT0"] = new TH1D( "hTPStationDeltaT0", "Delta t0 between MB1 and MB2; Delta t0 [ns]; Entries", 27, -10, 10);

        // ---------------------------------
        // Open the ROOT file
        TFile *file = new TFile( (inputDir+file_name).c_str() );

        // ---------------------------------
        // Open TDirectoryFile
        TDirectoryFile *dir;
        dir = (TDirectoryFile*)file->Get( "dtNtupleProducer" );

        // ---------------------------------
        // Open Tree
        TTree *tree = (TTree*)dir->Get("DTTREE");
        Long64_t nEntries = tree->GetEntries();


        // GEN information
        // --------------------------
        TBranch *branch_gen_nGenParts = tree->GetBranch("gen_nGenParts");
        int gen_nGenParts;
        branch_gen_nGenParts->SetAddress(&gen_nGenParts);

        std::vector<float> *gen_pdgId = nullptr;
        tree->SetBranchAddress("gen_pdgId", &gen_pdgId);
        std::vector<float> *gen_pt = nullptr;
        tree->SetBranchAddress("gen_pt", &gen_pt);
        std::vector<float> *gen_eta = nullptr;
        tree->SetBranchAddress("gen_eta", &gen_eta);
        std::vector<float> *gen_phi = nullptr;
        tree->SetBranchAddress("gen_phi", &gen_phi);

        // Segments (Reco Muon) information
        // --------------------------
        TBranch *branch_ph2Seg_nSegments = tree->GetBranch("ph2Seg_nSegments");
        int ph2Seg_nSegments;
        branch_ph2Seg_nSegments->SetAddress(&ph2Seg_nSegments);

        std::vector<float> *ph2Seg_wheel = nullptr;
        tree->SetBranchAddress("ph2Seg_wheel", &ph2Seg_wheel);
        std::vector<float> *ph2Seg_sector = nullptr;
        tree->SetBranchAddress("ph2Seg_sector", &ph2Seg_sector);
        std::vector<float> *ph2Seg_station = nullptr;
        tree->SetBranchAddress("ph2Seg_station", &ph2Seg_station);
        // std::vector<float> *ph2Seg_phiHits_superLayer = nullptr;
        // tree->SetBranchAddress("ph2Seg_phiHits_superLayer", &ph2Seg_phiHits_superLayer);
        std::vector<float> *ph2Seg_posLoc_x = nullptr;
        tree->SetBranchAddress("ph2Seg_posLoc_x", &ph2Seg_posLoc_x);
        std::vector<float> *ph2Seg_posLoc_y = nullptr;
        tree->SetBranchAddress("ph2Seg_posLoc_y", &ph2Seg_posLoc_y);
        std::vector<float> *ph2Seg_posGlb_phi = nullptr;
        tree->SetBranchAddress("ph2Seg_posGlb_phi", &ph2Seg_posGlb_phi);
        std::vector<float> *ph2Seg_posGlb_eta = nullptr;
        tree->SetBranchAddress("ph2Seg_posGlb_eta", &ph2Seg_posGlb_eta);
        std::vector<float> *ph2Seg_phi_t0 = nullptr;
        tree->SetBranchAddress("ph2Seg_phi_t0", &ph2Seg_phi_t0);
        std::vector<float> *ph2Seg_phi_nHits = nullptr;
        tree->SetBranchAddress("ph2Seg_phi_nHits", &ph2Seg_phi_nHits);
        std::vector<float> *ph2Seg_z_nHits = nullptr;
        tree->SetBranchAddress("ph2Seg_z_nHits", &ph2Seg_z_nHits);
        std::vector<float> *ph2Seg_dirLoc_x = nullptr;
        tree->SetBranchAddress("ph2Seg_dirLoc_x", &ph2Seg_dirLoc_x);
        std::vector<float> *ph2Seg_dirLoc_z = nullptr;
        tree->SetBranchAddress("ph2Seg_dirLoc_z", &ph2Seg_dirLoc_z);

        // Trigger Primitives information
        // --------------------------
        TBranch *branch_ph2TpgPhiEmuAm_nTrigs = tree->GetBranch("ph2TpgPhiEmuAm_nTrigs");
        int ph2TpgPhiEmuAm_nTrigs;
        branch_ph2TpgPhiEmuAm_nTrigs->SetAddress(&ph2TpgPhiEmuAm_nTrigs);

        std::vector<float> *ph2TpgPhiEmuAm_BX = nullptr;
        tree->SetBranchAddress("ph2TpgPhiEmuAm_BX", &ph2TpgPhiEmuAm_BX);
        std::vector<float> *ph2TpgPhiEmuAm_phi = nullptr;
        tree->SetBranchAddress("ph2TpgPhiEmuAm_phi", &ph2TpgPhiEmuAm_phi);
        std::vector<float> *ph2TpgPhiEmuAm_wheel = nullptr;
        tree->SetBranchAddress("ph2TpgPhiEmuAm_wheel", &ph2TpgPhiEmuAm_wheel);
        std::vector<float> *ph2TpgPhiEmuAm_sector = nullptr;
        tree->SetBranchAddress("ph2TpgPhiEmuAm_sector", &ph2TpgPhiEmuAm_sector);
        std::vector<float> *ph2TpgPhiEmuAm_station = nullptr;
        tree->SetBranchAddress("ph2TpgPhiEmuAm_station", &ph2TpgPhiEmuAm_station);
        std::vector<float> *ph2TpgPhiEmuAm_superLayer = nullptr;
        tree->SetBranchAddress("ph2TpgPhiEmuAm_superLayer", &ph2TpgPhiEmuAm_superLayer);
        std::vector<float> *ph2TpgPhiEmuAm_posLoc_x = nullptr;
        tree->SetBranchAddress("ph2TpgPhiEmuAm_posLoc_x", &ph2TpgPhiEmuAm_posLoc_x);
        std::vector<float> *ph2TpgPhiEmuAm_t0 = nullptr;
        tree->SetBranchAddress("ph2TpgPhiEmuAm_t0", &ph2TpgPhiEmuAm_t0);
        std::vector<float> *ph2TpgPhiEmuAm_quality = nullptr;
        tree->SetBranchAddress("ph2TpgPhiEmuAm_quality", &ph2TpgPhiEmuAm_quality);
        std::vector<float> *ph2TpgPhiEmuAm_rpcFlag = nullptr;
        tree->SetBranchAddress("ph2TpgPhiEmuAm_rpcFlag", &ph2TpgPhiEmuAm_rpcFlag);
        std::vector<float> *ph2TpgPhiEmuAm_index = nullptr;
        tree->SetBranchAddress("ph2TpgPhiEmuAm_index", &ph2TpgPhiEmuAm_index);
        std::vector<float> *ph2TpgPhiEmuAm_dirLoc_phi = nullptr;
        tree->SetBranchAddress("ph2TpgPhiEmuAm_dirLoc_phi", &ph2TpgPhiEmuAm_dirLoc_phi);
        

        double m_minMuPt = 20;
        m_minMuPt = 20;

        //m_maxMuSegDPhi = 0.3;
        // m_maxMuSegDPhi = 20;
        double m_maxMuSegDPhi = 0.1;
        //m_maxMuSegDEta = 0.4;
        //m_maxMuSegDEta = 20;
        double m_maxMuSegDEta = 0.15;
        
        double m_minSegHits = 4;
        double m_minZSegHits = 4;
        
        double m_maxSegTrigDPhi = 0.1;
        double m_maxMuTrigDPhi  = 0.2;
        
        double m_maxSegT0 = 15;

        int numTPAll = 0;
        int denTPAll = 0;
        int numTPEvent = 0;
        int denTPEvent = 0;
        int numTP = 0;
        int denTP = 0;
        int TPnotMatched = 0;

        std::vector<std::string> chambTags = { "MB1", "MB2", "MB3", "MB4"};
        std::vector<std::string> whTags    = { "Wh.-2", "Wh.-1", "Wh.0", "Wh.+1", "Wh.+2"};
        std::vector<std::string> secTags   = { "Sec1", "Sec2", "Sec3", "Sec4", "Sec5", "Sec6", "Sec7", "Sec8","Sec9","Sec10","Sec11","Sec12","Sec13","Sec14"};


        // for (const auto & secTag : secTags)
        // {
        //     m_plots["Eff_TPwheels_"+secTag+"_total"] = new TH1D(("Eff_TPwheels_"+secTag+"_total").c_str(),
        //     ("DT TP Local Efficiency for " + secTag + "; Wheel; Efficiency").c_str(), 22, 0, 22);
        //     m_plots["Eff_TPwheels_"+secTag+"_matched"] = new TH1D(("Eff_TPwheels_"+secTag+"_matched").c_str(),
        //     ("DT TP Local Efficiency for " + secTag + "; Wheel; Efficiency").c_str(), 22, 0, 22);
            
        //     m_plots["fakeRateTP_WheelvsStation_"+secTag+"_total"] = new TH1D(("fakeRateTP_WheelvsStation_"+secTag+"_total").c_str(),
        //     ("Fake Rate Wheel vs Station for " + secTag + "; Wheel; Fake Rate").c_str(), 22, 0, 22);
        //     m_plots["fakeRateTP_WheelvsStation_"+secTag+"_matched"] = new TH1D(("fakeRateTP_WheelvsStation_"+secTag+"_matched").c_str(),
        //     ("Fake Rate Wheel vs Station for " + secTag + "; Wheel; Fake Rate").c_str(), 22, 0, 22);

        //     m_plots["fakeRate_EventWheelStationTP_"+secTag+"_matched"] = new TH1D(("fakeRate_EventWheelStationTP_"+secTag+"_matched").c_str(),
        //     ("Fake Rate per event for " + secTag + "; Wheel; Fake TPs / Event").c_str(), 22, 0, 22);

        //     m_plots["fakeRate_TPnot_"+secTag+"_total"] = new TH1D(("fakeRate_TPnot_"+secTag+"_total").c_str(),
        //     ("TPs not Matched for " + secTag + "; Wheel; Fake Rate").c_str(), 22, 0, 22);
        //     m_plots["fakeRate_TPnot_"+secTag+"_matched"] = new TH1D(("fakeRate_TPnot_"+secTag+"_matched").c_str(),
        //     ("TPs not Matched for " + secTag + "; Wheel; Fake Rate").c_str(), 22, 0, 22);
        // }


        // ------------------------------------------------------------------------------
        // Loop in the events
        // ------------------------------------------------------------------------------
        // nEntries = 1;   // 100   nEntries
        if (testFlag){
            nEntries = 100;
            std::cout << "FOR TESTE:" <<std::endl;
        }
        std::cout << "Total entries:" << nEntries <<std::endl;

        int idxGen = 0;
        for (Long64_t iEvent = 0; iEvent < nEntries; ++iEvent) { 

            tree->GetEntry(iEvent);
            // branch_gen_nGenParts->GetEntry(iEvent);
            // branch_ph2TpgPhiEmuAm_nTrigs->GetEntry(iEvent);
            
            // m_plots["hNSeg"] -> Fill( ph2Seg_nSegments );
            // m_plots["hNTrigs"] -> Fill( ph2TpgPhiEmuAm_nTrigs );

            
            // for (std::size_t itrig = 0; itrig < ph2TpgPhiEmuAm_nTrigs; ++itrig){
            //     m_plots["htrigAMrpcFlag_Total"] -> Fill(ph2TpgPhiEmuAm_rpcFlag->at(itrig));
            //     m_plots["htrigAMBX_Total"] -> Fill(ph2TpgPhiEmuAm_BX->at(itrig));
            //     m_plots["trigAMt0_Total"] -> Fill(ph2TpgPhiEmuAm_t0->at(itrig));
            //     m_plots2["trigAMt0VsRpcFlag_Total"] -> Fill(ph2TpgPhiEmuAm_t0->at(itrig),ph2TpgPhiEmuAm_rpcFlag->at(itrig));
            // }

            std::vector<std::vector<int>> SegMatchedWheelAndStation;

            double RatioNtpNseg;
            RatioNtpNseg = double(ph2TpgPhiEmuAm_nTrigs) / double(ph2Seg_nSegments) ;
            // m_plots["hRatioNtpNseg_total"] -> Fill( RatioNtpNseg );

            numTPEvent = 0;
            denTPEvent = 0;
            TPnotMatched = 0;

            std::vector<int> vbestTPAM;
            // -----------------------------
            // loop Gen Particle
            // -----------------------------
            for (int iGenPart = 0; iGenPart < gen_nGenParts; ++iGenPart) {
                int numTP = 0;
                int denTP = 0;
                int NbestSegment = 0;
                int Ntrigger = 0;
                
                if (fdebug) std::cout << "==============================================================================" << std::endl;
                if (fdebug) std::cout << "iEvent " << iEvent << ", iGenPart " << iGenPart <<  " | gen_nGenParts: " << gen_nGenParts << " | " << "gen pt: "<< gen_pt->at(iGenPart) << " | " << "gen eta: "<< gen_eta->at(iGenPart) << " | gen phi: "<< gen_phi->at(iGenPart) << std::endl;
                if (fdebug) std::cout << "==============================================================================" << std::endl;

                m_plots["hGenIdPDG"] -> Fill( gen_pdgId->at(iGenPart) );
                m_plots["hGenEta"] -> Fill( gen_eta->at(iGenPart) );
                m_plots["hGenPt"] -> Fill( gen_pt->at(iGenPart) );
                // m_plots["EffEtaGenSeg_total"] -> Fill( gen_eta->at(iGenPart) );
                

                if (std::abs(gen_pdgId->at(iGenPart)) != 13 || gen_pt->at(iGenPart) < m_minMuPt) continue;

                // m_plots["EffEtaGenSeg20_total"] -> Fill( gen_eta->at(iGenPart) );

                // std::vector<std::size_t> bestSegIndex = { 999, 999, 999, 999 };
                // std::vector<Int_t> bestSegNHits       = { 0, 0, 0, 0 };

                int tempStation = 999;
                int tempLayer   = 999;
                int tempSector  = 999;
                int tempRing    = 999;
                std::vector<std::vector<double>> geo_info = barGeo.StaLaySecRing(gen_eta->at(iGenPart),gen_phi->at(iGenPart));
                for (size_t iGeo = 0; iGeo < geo_info.size(); ++iGeo) {
                    // 0=[station] 1=[layer] 2=[sector] 3=[ring]
                    int geoStation = geo_info[iGeo][0];
                    int geoLayer   = geo_info[iGeo][1];
                    int geoSector  = geo_info[iGeo][2];
                    int geoRing    = geo_info[iGeo][3];

                    // TODO: while we do not have stations 3 and 4 implemented in the TP build
                    if (geoStation == 3 || geoStation == 4) continue;

                    // To not repeat the chamber when a gen muon hit station 1 and station 2.
                    bool hitTwoLayers = false;
                    if (geoRing == tempRing && geoSector == tempSector && geoStation == tempStation && geoLayer > tempLayer ){
                        hitTwoLayers = true;
                        // continue;
                    }

                    tempStation = geo_info[iGeo][0];
                    tempLayer   = geo_info[iGeo][1];
                    tempSector  = geo_info[iGeo][2];
                    tempRing    = geo_info[iGeo][3];

                    if (hitTwoLayers){
                        std::cout << "hitTwoLayers:" << hitTwoLayers << std::endl;
                        std::cout << "Ring:" << geoRing << ", Sector: " << geoSector << ", Station: " << geoStation << ", Layer: " << geoLayer << std::endl;
                        continue;
                    }
                    else{
                        std::cout << "hitTwoLayers:" << hitTwoLayers << std::endl;
                        std::cout << "Ring:" << geoRing << ", Sector: " << geoSector << ", Station: " << geoStation << ", Layer: " << geoLayer << std::endl;
                    }
                }

                // -----------------------------
                // Loop in the AM TP
                // -----------------------------
                if (fdebug) std::cout << "      Loop in the AM TP " << std::endl;
                if (fdebug) std::cout << "      Total number of TP in this event: "<< ph2TpgPhiEmuAm_nTrigs << std::endl;
                
                std::vector<int> bestTP;
                for (std::size_t iTrigAM = 0; iTrigAM < ph2TpgPhiEmuAm_nTrigs; ++iTrigAM){

                    Int_t trigAMWh  = ph2TpgPhiEmuAm_wheel->at(iTrigAM);
                    Int_t trigAMSec = ph2TpgPhiEmuAm_sector->at(iTrigAM);
                    Int_t trigAMSt  = ph2TpgPhiEmuAm_station->at(iTrigAM);
                    Int_t trigAMBX  = ph2TpgPhiEmuAm_BX->at(iTrigAM);
                    Int_t trigAMqual = ph2TpgPhiEmuAm_quality->at(iTrigAM);
                    Int_t trigAMrpc  = ph2TpgPhiEmuAm_rpcFlag->at(iTrigAM);

                    if (trigAMBX != 20) continue;

                    if (fileRPCflag){
                        if (flagRPCselection == 1){
                            if ( trigAMrpc != 1 ) continue;
                        }
                        else if (flagRPCselection == 2){
                            if ( trigAMrpc != 2 ) continue;
                        }
                        else if (flagRPCselection == 3){
                            if ( trigAMrpc != 3 ) continue;
                        }
                        else if (flagRPCselection == 10){
                            if ( trigAMrpc != 1 && trigAMrpc != 0 ) continue;
                        }
                    }
                    
                    // For this file, we are ignoring the RPC flags 0 and 1 to simulate only RPC TPs
                    if ( name == "RPCOnly" || name == "RPCOnlyUpdated" ){
                        if (trigAMrpc == 0) continue;
                        if (trigAMrpc == 1) continue;
                    }


                    // int tempStation = 999;
                    // int tempLayer   = 999;
                    // int tempSector  = 999;
                    // int tempRing    = 999;
                    
                    for (size_t iGeo = 0; iGeo < geo_info.size(); ++iGeo) {
                        // 0=[station] 1=[layer] 2=[sector] 3=[ring]
                        int geoStation = geo_info[iGeo][0];
                        int geoLayer   = geo_info[iGeo][1];
                        int geoSector  = geo_info[iGeo][2];
                        int geoRing    = geo_info[iGeo][3];

                        // TODO: while we do not have stations 3 and 4 implemented in the TP build
                        if (geoStation == 3 || geoStation == 4) continue;

                        // To not repeat the chamber when a gen muon hit station 1 and station 2.
                        bool hitTwoLayers = false;
                        if (geoRing == tempRing && geoSector == tempSector && geoStation == tempStation && geoLayer > tempLayer ){
                            hitTwoLayers = true;
                            // continue;
                        }

                        tempStation = geo_info[iGeo][0];
                        tempLayer   = geo_info[iGeo][1];
                        tempSector  = geo_info[iGeo][2];
                        tempRing    = geo_info[iGeo][3];

                        if (hitTwoLayers){
                            // std::cout << "hitTwoLayers:" << hitTwoLayers << std::endl;
                            // std::cout << "Ring:" << geoRing << ", Sector: " << geoSector << ", Station: " << geoStation << ", Layer: " << geoLayer << std::endl;
                            continue;
                        }
                        // else{
                        //     std::cout << "hitTwoLayers:" << hitTwoLayers << std::endl;
                        //     std::cout << "Ring:" << geoRing << ", Sector: " << geoSector << ", Station: " << geoStation << ", Layer: " << geoLayer << std::endl;
                        // }

                        // -----------------------------
                        // GEN AND TP MATCHING
                        // -----------------------------
                        if (geoRing == trigAMWh && geoSector == trigAMSec && geoStation  == trigAMSt) {

                            Double_t trigGlbPhi    = trigPhiInRad(ph2TpgPhiEmuAm_phi->at(iTrigAM),trigAMSec);
                            Double_t trigAMt0 = ph2TpgPhiEmuAm_t0->at(iTrigAM);

                            trigAMt0 = (trigAMt0 * 25 / 32); // DCS to ns
                            trigAMt0 = trigAMt0 - 390; // Shift to zero (RPC only)

                            if (fdebug) std::cout << " iTrigAM: " << iTrigAM << " | Wh: "<< trigAMWh << 
                                                     " | Sec: " << trigAMSec << " | St: " << trigAMSt << 
                                                     " | BX: " << trigAMBX << " | GlbPhi: " << trigGlbPhi  <<
                                                     " | t0: " << trigAMt0 << std::endl;
                            
                            m_plots["hGenTPdeltaPhi"] -> Fill( gen_phi->at(iGenPart) - trigGlbPhi );

                            bestTP.push_back(iTrigAM);

                        }


                    }// End loop Geo
                } // END loop Trigger primitives

                std::cout << "bestTP size: " << bestTP.size() << std::endl;
                for (std::size_t ibestTP = 0; ibestTP < bestTP.size(); ++ibestTP){

                    Int_t trigAMWh  = ph2TpgPhiEmuAm_wheel->at(bestTP[ibestTP]);
                    Int_t trigAMSec = ph2TpgPhiEmuAm_sector->at(bestTP[ibestTP]);
                    Int_t trigAMSt  = ph2TpgPhiEmuAm_station->at(bestTP[ibestTP]);
                    Double_t trigAMt0 = ph2TpgPhiEmuAm_t0->at(bestTP[ibestTP]);
                    trigAMt0 = (trigAMt0 * 25 / 32); // DCS to ns
                    trigAMt0 = trigAMt0 - 390; // Shift to zero (RPC only)

                    std::cout << "bestTP 1: "  <<  "trigAMt0 :" << trigAMt0 << std::endl;


                    // For time between station 1 and station 2
                    for (std::size_t jbestTP = 0; jbestTP < bestTP.size(); ++jbestTP){
                        
                        Int_t trigAMWh2  = ph2TpgPhiEmuAm_wheel->at(bestTP[jbestTP]);
                        Int_t trigAMSec2 = ph2TpgPhiEmuAm_sector->at(bestTP[jbestTP]);
                        Int_t trigAMSt2  = ph2TpgPhiEmuAm_station->at(bestTP[jbestTP]);

                        if ( bestTP[jbestTP] == bestTP[ibestTP] ) continue;

                        // To not repeat combinations
                        if ( ibestTP > jbestTP) continue;
                        
                        Double_t trigAMt02 = ph2TpgPhiEmuAm_t0->at(bestTP[jbestTP]);
                        trigAMt02 = (trigAMt02 * 25 / 32); // DCS to ns
                        trigAMt02 = trigAMt02 - 390; // Shift to zero (RPC only)
                        std::cout << "bestTP 2: "  <<  "trigAMt02 :" << trigAMt0 << std::endl;

                        if ( trigAMWh == trigAMWh2 && trigAMSec == trigAMSec2 && trigAMSt != trigAMSt2 ){

                            std::cout << "MB1 t0 - MB2 t0: " << trigAMt0 - trigAMt02 << std::endl;
                            m_plots["hTPStationDeltaT0"] -> Fill( trigAMt0 - trigAMt02 );

                            std::cout << "Filled " << std::endl;


                        }
                        else{
                            continue;
                        }


                    }



                }

                
            } // END Loop Gen

        } // END Loop Event


        // for (const auto & secTag : secTags)
        // {
        //     m_plots["fakeRate_EventWheelStationTP_"+secTag+"_matched"]->Scale(1.0 / nEntries);
        // }

        // -----------------------------------------------------------------
        // Creating directories to save control plots and root files
        // -----------------------------------------------------------------
        std::string outputDir = "";
        std::string histoDir = "";
        std::string effDir = "";
        // if (file_name.find("noRPC") != std::string::npos)

        // if (fdebug) std::cout << "Found '"<< m_files[name] <<"' in the filename!" << std::endl;
        outputDir = "output/"+name+"/";
        histoDir =  "output/"+name+"/histograms/";
        effDir =    "output/"+name+"/histograms/effPlots/";

        // Create the directory if it doesn't exist
        if (gSystem->AccessPathName(outputDir.c_str())) {
            gSystem->mkdir(outputDir.c_str(), true); // true = recursive
        }

        if (gSystem->AccessPathName(histoDir.c_str())) {
            gSystem->mkdir(histoDir.c_str(), true); // true = recursive
        }

        if (gSystem->AccessPathName(effDir.c_str())) {
            gSystem->mkdir(effDir.c_str(), true); // true = recursive
        }
        
        const std::string& outputFile = "DTNtupleTPGSimAnalyzer_Efficiency.root";
        // Create a new ROOT file (recreate will overwrite existing file)
        TFile outFile((outputDir+outputFile).c_str(), "RECREATE");
        // Check if file opened successfully
        if (!outFile.IsOpen()) {
            std::cerr << "Error: Could not create file " << (outputDir+outputFile) << std::endl;
            return 1;
        }

        // -------------------------------------------
        // Loop over the map to save each histogram in the root file and as png
        // -------------------------------------------
        if (plotHistograms){
            for (const auto& pair : m_plots) {
                const std::string& name = pair.first;
                TH1* hist = pair.second;

                if (!hist) {
                    std::cerr << "Warning: Histogram '" << name << "' is null!" << std::endl;
                    continue;
                }
                hist->Write(); // Write the histogram to the root file

                // Create a canvas to draw the histogram
                TCanvas canvas("canvas", "canvas", 800, 600);
                hist->Draw();

                // Save the plot in the output directory
                gErrorIgnoreLevel = kError;  // or kWarning
                canvas.SaveAs((histoDir + name + ".png").c_str());
                gErrorIgnoreLevel = kInfo;  // Back to normal

                // Need to apply do not receve Warning in <TROOT::Append>: Replacing existing TH1 (Potential memory leak).
                delete hist;
            }

            for (const auto& pair : m_plots2) {
                const std::string& name = pair.first;
                TH2* hist = pair.second;

                if (!hist) {
                    std::cerr << "Warning: Histogram '" << name << "' is null!" << std::endl;
                    continue;
                }
                hist->Write(); // Write the histogram to the root file

                // Create a canvas to draw the histogram
                TCanvas canvas("canvas", "canvas", 800, 600);
                // hist->Draw();
                hist->SetMarkerStyle(20);   // 20 = small dots
                hist->SetMarkerColor(kBlack); // kBlack = ROOT's black color
                hist->SetMarkerSize(0.5);   // Adjust dot size (optional)
                hist->Draw("P");  // "P" option draws only points
                // hist->Draw("AP");
                // Save the plot in the output directory
                gErrorIgnoreLevel = kError;  // or kWarning
                canvas.SaveAs((histoDir + name + ".png").c_str());
                gErrorIgnoreLevel = kInfo;  // Back to normal

                delete hist;
            }
        }

        // // Close the file (optional, as it will be automatically closed when outFile goes out of scope)
        // outFile.Close();
        // std::cout << "All histograms saved in ROOT file: " << outputFile << std::endl;
        // std::cout << "All plots saved in: " << outputDir << std::endl;
        // std::cout << "booltest: " << booltest << std::endl;
        
    }

    // std::cout << "----------------------------------" << std::endl;
    // std::cout << "TEST FLAG: " << testFlag << std::endl;
    // std::cout << "plotHistograms FLAG: " << plotHistograms << std::endl;
    // std::cout << "flag RPC: " << flagRPCselection << std::endl;
    // std::cout << "----------------------------------" << std::endl;

    return 0;
} // END Program