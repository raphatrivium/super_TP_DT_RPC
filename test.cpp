// This code is a modificated version file to run locally of the DTNtupleTPGSimAnalyzer_Efficiency.cpp 
// that can be found in the github: 
// https://github.com/jaimeleonh/DTNtuples/blob/unifiedPerf/test/DTNtupleTPGSimAnalyzer_Efficiency.C


#include "DTNtupleTPGSimAnalyzer.h"

int test() { 

    bool testFlag = false;   // false - true
    bool fdebug = true;

    bool plotHistograms = true; // false - true

    // ------------------------------------------------------------------------------
    // INPUT FILES
    // ------------------------------------------------------------------------------
    std::string inputDir = "input/";
    std::map<std::string,std::string> m_files;
    // m_files["DTAM"]              = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_step2_noRPC.root";
    // m_files["RPC"]               = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_step2_RPC.root";
    // m_files["RPC_Flag1"]         = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_step2_RPC.root";
    // m_files["RPC_Flag2"]         = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_step2_RPC.root";
    // m_files["DTAMUpdated"]       = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_noRPC_PHASE2_TN_33BX.root";
    // m_files["RPCUpdated"]        = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_withRPC_PHASE2_TN_33BX.root";
    // m_files["DTRPCOnly"]        = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_Dec2025.root";
    // m_files["RPCOnly"]         = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_Dec2025.root";
    m_files["RPCOnly"]         = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_OldSample_WithRPCDIGISIM.root";
    // m_files["RPCOnlyUpdated"]  = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_RPCPhase2_RPCOnlyFlag.root";
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

        // BarrelGeo barGeo("barrel_geometry.txt");
        BarrelGeo barGeo;
        if ( name == "RPCOnly" || name == "RPCOnlyUpdated" ) barGeo = BarrelGeo("barrel_geometry.txt");
   
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

        std::vector<std::string> chambTags = { "MB1", "MB2", "MB3", "MB4"};
        std::vector<std::string> whTags    = { "Wh.-2", "Wh.-1", "Wh.0", "Wh.+1", "Wh.+2"};
        std::vector<std::string> secTags   = { "Sec1", "Sec2", "Sec3", "Sec4", "Sec5", "Sec6", "Sec7", "Sec8","Sec9","Sec10","Sec11","Sec12","Sec13","Sec14"};

        m_plots["hGenEta"] = new TH1D("hGenEta", "Gen Muon #eta distribution ; #eta; Entries", 200, -1.5, +1.5);
        m_plots["hGenPt"] = new TH1D("hGenPt", "Gen Muon pT distribution ; pT; Entries", 200, 0, 200);
        m_plots["hGenIdPDG"] = new TH1D("hGenIdPDG", "Gen PDG ID ; PDG ID; Entries", 40, -20, 20);

        // m_plots["EffEtaGenSeg_total"] = new TH1D("EffEtaGenSeg_total", "Muon Reconstruction Efficiency; #eta; Efficiency", 100, -2, 2);

        m_plots["hNTrigs"] = new TH1D("hNTrigs", "Number of Triggers ; Number of Triggers; Entries / Event", 50, 0, 300);
        m_plots["hTrigFlag"] = new TH1D("hTrigFlag", "Trigger Primitive RPC Flag; RPC Flag; Entries", 5, 0, 5);

        m_plots["hGenTPdeltaPhi"] = new TH1D("hGenTPdeltaPhi", "Delta Phi between Gen and TP ; Delta Phi; Entries", 600, 0, 0.5);


        m_plots["hTpT0_matched_DCS"] = new TH1D("hTpT0_matched_DCS", "Time Distribution of the Trigger Primitives;t0 [DCS];Entries", 40, 630, 650);
        m_plots["hTpT0_matched_ns"]  = new TH1D("hTpT0_matched_ns", "Time Distribution of the Trigger Primitives;t0 [ns];Entries", 40, -20, 20);

        // m_plots["hTP_MB1_MB2_DeltaT0"] = new TH1D( "hTP_MB1_MB2_DeltaT0", "Delta t0 between MB1 and MB2; Delta t0 [ns]; Entries", 30, 0, 10);
        m_plots["hTP_MB1_MB2_DeltaT0"] = new TH1D( "hTP_MB1_MB2_DeltaT0", "Delta t0 between MB1 and MB2; Delta t0 [ns]; Entries", 60, -10, 10);

        m_plots["Eff_TPwheels_total"] = new TH1D("Eff_TPwheels_total", "RPC TP Local Efficiency; Wheel; Efficiency", 22, 0, 22);
        m_plots["Eff_TPwheels_matched"] = new TH1D("Eff_TPwheels_matched", "RPC TP Local Efficiency; Wheel; Efficiency",22, 0, 22);

        for (const auto & chamb : chambTag) {
            for (const auto & wheel : wheelTag) {
                // m_plots["hGenSegDeltaPhi"+wheel+chamb] = new TH1D(("hGenSegDeltaPhi"+wheel+chamb).c_str(),
                // "Gen Muon - Segment Delta Phi distribution ; Delta Phi; Entries", 600, 0, 0.5);
                // m_plots["hGenSegDeltaEta"+wheel+chamb] = new TH1D(("hGenSegDeltaEta"+wheel+chamb).c_str(),
                // "Gen Muon - Segment Delta Eta distribution ; Delta Eta; Entries", 600, 0,  0.5);

                m_plots["hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched"] = new TH1D( ("hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched").c_str(),
                ("hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched; Time of the TPs associated with prompt muons [ns]; Entries").c_str(), 27, -10, 10); // 40, 0, 700  // 40, 630, 650

                m_plots["hPh2TpgPhiEmuAmBX"+wheel+chamb+"_matched"] = new TH1D( ("hPh2TpgPhiEmuAmBX"+wheel+chamb+"_matched").c_str(),
                ("hPh2TpgPhiEmuAmBX"+wheel+chamb+"_matched; BXs of the TPs associated with prompt muons [ns]; Entries").c_str(), 20, 10, 30);

            }
        }

        m_plots["fakeRate_WheelStationTP_total"] = new TH1D("fakeRate_WheelStationTP_total", "Trigger Primitive not Matched; Wheel; Fake Rate",  22, 0, 22);
        m_plots["fakeRate_WheelStationTP_matched"] = new TH1D("fakeRate_WheelStationTP_matched", "Trigger Primitive not Matched; Wheel; Fake Rate",  22, 0, 22);

        m_plots["fakeRate_TP_total"] = new TH1D("fakeRate_TP_total", "Trigger Primitive not Matched; Wheel; Fake Rate",  22, 0, 22);
        m_plots["fakeRate_TP_matched"] = new TH1D("fakeRate_TP_matched", "Trigger Primitive not Matched; Wheel; Fake Rate",  22, 0, 22);

        for (const auto & secTag : secTags)
        {
            m_plots["Eff_TPwheels_"+secTag+"_total"] = new TH1D(("Eff_TPwheels_"+secTag+"_total").c_str(),
            ("DT TP Local Efficiency for " + secTag + "; Wheel; Efficiency").c_str(), 22, 0, 22);
            m_plots["Eff_TPwheels_"+secTag+"_matched"] = new TH1D(("Eff_TPwheels_"+secTag+"_matched").c_str(),
            ("DT TP Local Efficiency for " + secTag + "; Wheel; Efficiency").c_str(), 22, 0, 22);
            
        //     m_plots["fakeRateTP_WheelvsStation_"+secTag+"_total"] = new TH1D(("fakeRateTP_WheelvsStation_"+secTag+"_total").c_str(),
        //     ("Fake Rate Wheel vs Station for " + secTag + "; Wheel; Fake Rate").c_str(), 22, 0, 22);
        //     m_plots["fakeRateTP_WheelvsStation_"+secTag+"_matched"] = new TH1D(("fakeRateTP_WheelvsStation_"+secTag+"_matched").c_str(),
        //     ("Fake Rate Wheel vs Station for " + secTag + "; Wheel; Fake Rate").c_str(), 22, 0, 22);

        //     m_plots["fakeRate_EventWheelStationTP_"+secTag+"_matched"] = new TH1D(("fakeRate_EventWheelStationTP_"+secTag+"_matched").c_str(),
        //     ("Fake Rate per event for " + secTag + "; Wheel; Fake TPs / Event").c_str(), 22, 0, 22);

            m_plots["fakeRate_TP_"+secTag+"_total"] = new TH1D(("fakeRate_TP_"+secTag+"_total").c_str(),
            ("TPs not Matched for " + secTag + "; Wheel; Fake Rate").c_str(), 22, 0, 22);
            m_plots["fakeRate_TP_"+secTag+"_matched"] = new TH1D(("fakeRate_TP_"+secTag+"_matched").c_str(),
            ("TPs not Matched for " + secTag + "; Wheel; Fake Rate").c_str(), 22, 0, 22);

            // m_plots["Eff_TPwheels_"+secTag+"_total"] = new TH1D(("Eff_TPwheels_"+secTag+"_total").c_str(),
            // ("TPs not Matched for " + secTag + "; Wheel; Fake Rate").c_str(), 22, 0, 22);
            // m_plots["Eff_TPwheels_"+secTag+"_matched"] = new TH1D(("Eff_TPwheels_"+secTag+"_matched").c_str(),
            // ("TPs not Matched for " + secTag + "; Wheel; Fake Rate").c_str(), 22, 0, 22);

        }

        m_plots["hNSimLinks"] = new TH1D("hNSimLinks", "Number of RPC SimLinks per Event; Number of RPC SimLinks; Entries / Event", 50, 0, 800);
        m_plots["hNSimLinksPDG13"] = new TH1D("hNSimLinksPDG13", "Number of RPC SimLinks related to Muons per Event; Number of RPC SimLinks; Entries / Event", 50, 0, 200);

        m_plots["hNSimLinkIdPDG"] = new TH1D("hNSimLinkIdPDG", "RPC SimLinks Particle ID; Particle ID; Entries", 30, 0, 30);

        m_plots["hSimLinkTPdeltaPhi"] = new TH1D("hSimLinkTPdeltaPhi", "Delta Phi between SimLink and TP ; Delta Phi; Entries", 600, 0, 0.5);


        
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

        // RPC SimLink information
        // --------------------------
        TBranch *branch_rpcSimLink_nSimLinks = tree->GetBranch("rpcSimLink_nSimLinks");
        int rpcSimLink_nSimLinks;
        branch_rpcSimLink_nSimLinks->SetAddress(&rpcSimLink_nSimLinks);

        std::vector<float> *rpcSimLink_particleId = nullptr;
        tree->SetBranchAddress("rpcSimLink_particleId", &rpcSimLink_particleId);
        std::vector<float> *rpcSimLink_global_eta = nullptr;
        tree->SetBranchAddress("rpcSimLink_global_eta", &rpcSimLink_global_eta);
        std::vector<float> *rpcSimLink_global_phi = nullptr;
        tree->SetBranchAddress("rpcSimLink_global_phi", &rpcSimLink_global_phi);
        std::vector<float> *rpcSimLink_ring = nullptr;
        tree->SetBranchAddress("rpcSimLink_ring", &rpcSimLink_ring);
        std::vector<float> *rpcSimLink_station = nullptr;
        tree->SetBranchAddress("rpcSimLink_station", &rpcSimLink_station);
        std::vector<float> *rpcSimLink_layer = nullptr;
        tree->SetBranchAddress("rpcSimLink_layer", &rpcSimLink_layer);
        std::vector<float> *rpcSimLink_sector = nullptr;
        tree->SetBranchAddress("rpcSimLink_sector", &rpcSimLink_sector);
        std::vector<float> *rpcSimLink_bx = nullptr;
        tree->SetBranchAddress("rpcSimLink_bx", &rpcSimLink_bx);
        std::vector<int> *rpcSimLink_TrackId = nullptr;
        tree->SetBranchAddress("rpcSimLink_TrackId", &rpcSimLink_TrackId);
        std::vector<int> *rpcSimLink_ProcessType = nullptr;
        tree->SetBranchAddress("rpcSimLink_ProcessType", &rpcSimLink_ProcessType);

        // Segments (Reco Muon) information
        // --------------------------
        // TBranch *branch_ph2Seg_nSegments = tree->GetBranch("ph2Seg_nSegments");
        // int ph2Seg_nSegments;
        // branch_ph2Seg_nSegments->SetAddress(&ph2Seg_nSegments);

        // std::vector<float> *ph2Seg_wheel = nullptr;
        // tree->SetBranchAddress("ph2Seg_wheel", &ph2Seg_wheel);
        // std::vector<float> *ph2Seg_sector = nullptr;
        // tree->SetBranchAddress("ph2Seg_sector", &ph2Seg_sector);
        // std::vector<float> *ph2Seg_station = nullptr;
        // tree->SetBranchAddress("ph2Seg_station", &ph2Seg_station);
        // // std::vector<float> *ph2Seg_phiHits_superLayer = nullptr;
        // // tree->SetBranchAddress("ph2Seg_phiHits_superLayer", &ph2Seg_phiHits_superLayer);
        // std::vector<float> *ph2Seg_posLoc_x = nullptr;
        // tree->SetBranchAddress("ph2Seg_posLoc_x", &ph2Seg_posLoc_x);
        // std::vector<float> *ph2Seg_posLoc_y = nullptr;
        // tree->SetBranchAddress("ph2Seg_posLoc_y", &ph2Seg_posLoc_y);
        // std::vector<float> *ph2Seg_posGlb_phi = nullptr;
        // tree->SetBranchAddress("ph2Seg_posGlb_phi", &ph2Seg_posGlb_phi);
        // std::vector<float> *ph2Seg_posGlb_eta = nullptr;
        // tree->SetBranchAddress("ph2Seg_posGlb_eta", &ph2Seg_posGlb_eta);
        // std::vector<float> *ph2Seg_phi_t0 = nullptr;
        // tree->SetBranchAddress("ph2Seg_phi_t0", &ph2Seg_phi_t0);
        // std::vector<float> *ph2Seg_phi_nHits = nullptr;
        // tree->SetBranchAddress("ph2Seg_phi_nHits", &ph2Seg_phi_nHits);
        // std::vector<float> *ph2Seg_z_nHits = nullptr;
        // tree->SetBranchAddress("ph2Seg_z_nHits", &ph2Seg_z_nHits);
        // std::vector<float> *ph2Seg_dirLoc_x = nullptr;
        // tree->SetBranchAddress("ph2Seg_dirLoc_x", &ph2Seg_dirLoc_x);
        // std::vector<float> *ph2Seg_dirLoc_z = nullptr;
        // tree->SetBranchAddress("ph2Seg_dirLoc_z", &ph2Seg_dirLoc_z);

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

        int numTPAll = 0;
        int denTPAll = 0;
        int numTPEvent = 0;
        int denTPEvent = 0;
        int numTP = 0;
        int denTP = 0;
        int TPnotMatched = 0;

        // ------------------------------------------------------------------------------
        // Loop in the events
        // ------------------------------------------------------------------------------
        // nEntries = 10;   // 100   nEntries
        if (testFlag){
            nEntries = 100;
            std::cout << "FOR TESTE:" <<std::endl;
        }
        std::cout << "Total entries:" << nEntries <<std::endl;

        int idxGen = 0;
        bool flagFill = false;

        
        for (Long64_t iEvent = 0; iEvent < nEntries; ++iEvent) {

            if (fdebug) std::cout << "=================================" << std::endl;
            if (fdebug) std::cout << "iEvent " << iEvent << std::endl;
            if (fdebug) std::cout << "=================================" << std::endl;

            tree->GetEntry(iEvent);
            // branch_gen_nGenParts->GetEntry(iEvent);
            // branch_ph2TpgPhiEmuAm_nTrigs->GetEntry(iEvent);
            
            // m_plots["hNSeg"] -> Fill( ph2Seg_nSegments );
            
            // for (std::size_t itrig = 0; itrig < ph2TpgPhiEmuAm_nTrigs; ++itrig){
            //     m_plots["htrigAMrpcFlag_Total"] -> Fill(ph2TpgPhiEmuAm_rpcFlag->at(itrig));
            //     m_plots["htrigAMBX_Total"] -> Fill(ph2TpgPhiEmuAm_BX->at(itrig));
            //     m_plots["trigAMt0_Total"] -> Fill(ph2TpgPhiEmuAm_t0->at(itrig));
            //     m_plots2["trigAMt0VsRpcFlag_Total"] -> Fill(ph2TpgPhiEmuAm_t0->at(itrig),ph2TpgPhiEmuAm_rpcFlag->at(itrig));
            // }

            // std::vector<std::vector<int>> SegMatchedWheelAndStation;

            // double RatioNtpNseg;
            // RatioNtpNseg = double(ph2TpgPhiEmuAm_nTrigs) / double(ph2Seg_nSegments) ;
            // m_plots["hRatioNtpNseg_total"] -> Fill( RatioNtpNseg );

            // numTPEvent = 0;
            // denTPEvent = 0;
            // TPnotMatched = 0;

            int coutNTrigs = 0;

            // -----------------------------
            // Loop in the AM TP
            // -----------------------------
            if (fdebug) std::cout << "Loop in the AM TP " << std::endl;
            if (fdebug) std::cout << "Total number of TP in this event: "<< ph2TpgPhiEmuAm_nTrigs << std::endl;
            
            std::vector<int> selectedTP;
            for (std::size_t iTrigAM = 0; iTrigAM < ph2TpgPhiEmuAm_nTrigs; ++iTrigAM){

                Int_t trigAMWh  = ph2TpgPhiEmuAm_wheel->at(iTrigAM);
                // Int_t trigAMSec = ph2TpgPhiEmuAm_sector->at(iTrigAM);
                Int_t trigAMSt  = ph2TpgPhiEmuAm_station->at(iTrigAM);
                Int_t trigAMBX  = ph2TpgPhiEmuAm_BX->at(iTrigAM);
                // Int_t trigAMqual = ph2TpgPhiEmuAm_quality->at(iTrigAM);
                Int_t trigAMrpc  = ph2TpgPhiEmuAm_rpcFlag->at(iTrigAM);

                if ( name == "RPCOnly" || name == "RPCOnlyUpdated" ) {
                    if ( trigAMrpc != 2 ) continue;
                }

                // if ( name == "RPCOnly" || name == "RPCOnlyUpdated" ) {
                //     if ( trigAMrpc == 0 ) continue;
                //     if ( trigAMrpc == 1 ) continue;
                // }
                
                m_plots["hTrigFlag"] -> Fill( trigAMrpc );
                coutNTrigs++;
                
                if (trigAMBX != 20) continue;

                selectedTP.push_back(iTrigAM);

            }
            if (fdebug) std::cout << "selectedTP.size() " << selectedTP.size() << std::endl;

            m_plots["hNTrigs"] -> Fill( coutNTrigs );
            
            int coutNrpcSimLink = 0;
            // -----------------------------
            // Loop in the rpcSimLink
            // -----------------------------
            if (fdebug) std::cout << "Loop in the rpcSimLink " << std::endl;
            if (fdebug) std::cout << "Total number of SimLink in this event: "<< rpcSimLink_nSimLinks << std::endl;
            
            // -----------------------------
            // To elimiante duplicates - each muon can generate 2-3 digis in a chamber.
            std::vector<int> vSimLink;
            bool vSimLinkFilled = false;
            for (int iSimLink = 0; iSimLink < rpcSimLink_nSimLinks; ++iSimLink) {

                if (  std::abs(rpcSimLink_particleId->at(iSimLink)) != 13) continue;

                Int_t SimLinkRing    = rpcSimLink_ring->at(iSimLink);
                Int_t SimLinkSector  = rpcSimLink_sector->at(iSimLink);
                Int_t SimLinkStation = rpcSimLink_station->at(iSimLink);
                Int_t SimLinkLayer   = rpcSimLink_layer->at(iSimLink);

                if (vSimLinkFilled == false){
                    vSimLink.push_back(iSimLink);
                    vSimLinkFilled = true;
                    continue;
                }

                bool flagDuplicate = false;
                for (int iSimLink2 = 0; iSimLink2 < vSimLink.size(); ++iSimLink2){

                    // if ( iSimLink == iSimLink2 ) continue; // To avoid self combinations
                    // if ( iSimLink > iSimLink2) continue; // To avoid repeated combinations: "01" and "10"

                    Int_t SimLinkRing2    = rpcSimLink_ring->at(vSimLink[iSimLink2]);
                    Int_t SimLinkSector2  = rpcSimLink_sector->at(vSimLink[iSimLink2]);
                    Int_t SimLinkStation2 = rpcSimLink_station->at(vSimLink[iSimLink2]);
                    Int_t SimLinkLayer2   = rpcSimLink_layer->at(vSimLink[iSimLink2]);

                    if ( SimLinkRing == SimLinkRing2 && SimLinkSector == SimLinkSector2 && 
                    SimLinkStation == SimLinkStation2 && SimLinkLayer == SimLinkLayer2 ){
                        flagDuplicate = true;
                        break;  
                    } 
                }

                if (flagDuplicate == false) vSimLink.push_back(iSimLink);
                

            }
            if (fdebug) std::cout << "vSimLink.size(): "<< vSimLink.size() << std::endl;

            // for (int iSimLink = 0; iSimLink < vSimLink.size(); ++iSimLink) {
                
            //     Int_t SimLinkRing    = rpcSimLink_ring->at(vSimLink[iSimLink]);
            //     Int_t SimLinkSector  = rpcSimLink_sector->at(vSimLink[iSimLink]);
            //     Int_t SimLinkStation = rpcSimLink_station->at(vSimLink[iSimLink]);
            //     Int_t SimLinkLayer   = rpcSimLink_layer->at(vSimLink[iSimLink]);
            //     Int_t SimLinkBx      = rpcSimLink_bx->at(vSimLink[iSimLink]);
            //     Int_t SimTrackID     = rpcSimLink_TrackId->at(vSimLink[iSimLink]);
            //     Int_t SimProType     = rpcSimLink_ProcessType->at(vSimLink[iSimLink]);

            //     if (fdebug) std::cout << "iEvent " << iEvent << ", vSimLink " << vSimLink[iSimLink] << ", partID " << rpcSimLink_particleId->at(vSimLink[iSimLink]) 
            //                           << " | " << "eta: "<< rpcSimLink_global_eta->at(vSimLink[iSimLink]) << " | phi: "<< rpcSimLink_global_phi->at(vSimLink[iSimLink])
            //                           << " | " << "Wh: "<< SimLinkRing << " | Sec: "<< SimLinkSector << " | " << "St: "<< SimLinkStation
            //                           << " | " << "Lay: "<< SimLinkLayer << " | Bx: "<< SimLinkBx << " | TrackID: "<< SimTrackID 
            //                           << " | " << "ProType: "<< SimProType << std::endl;
            // }

            if (fdebug) std::cout << "\n" << std::endl;
            // -----------------------------
            // Update the vector to select to keep the only Simlinks that have two layer hit.
            std::vector<int> vTemp; // Temporary vector
            for (int iSimLink = 0; iSimLink < vSimLink.size(); ++iSimLink) {

                Int_t SimLinkRing    = rpcSimLink_ring->at(vSimLink[iSimLink]);
                Int_t SimLinkSector  = rpcSimLink_sector->at(vSimLink[iSimLink]);
                Int_t SimLinkStation = rpcSimLink_station->at(vSimLink[iSimLink]);
                Int_t SimLinkLayer   = rpcSimLink_layer->at(vSimLink[iSimLink]);
                Int_t SimLinkBx      = rpcSimLink_bx->at(vSimLink[iSimLink]);
                Int_t SimTrackID     = rpcSimLink_TrackId->at(vSimLink[iSimLink]);
                Int_t SimProType     = rpcSimLink_ProcessType->at(vSimLink[iSimLink]);

                if (SimProType != 0) continue;

                // if (fdebug) std::cout << "vSimLink " vSimLink[iSimLink]<< std::endl;

                bool flag2LayerHit = false;
                for (int iSimLink2 = 0; iSimLink2 < vSimLink.size(); ++iSimLink2){

                    // if (fdebug) std::cout << "vSimLink " vSimLink[iSimLink]<< std::endl;

                    Int_t SimLinkRing2    = rpcSimLink_ring->at(vSimLink[iSimLink2]);
                    Int_t SimLinkSector2  = rpcSimLink_sector->at(vSimLink[iSimLink2]);
                    Int_t SimLinkStation2 = rpcSimLink_station->at(vSimLink[iSimLink2]);
                    Int_t SimLinkLayer2   = rpcSimLink_layer->at(vSimLink[iSimLink2]);
                    // Int_t SimProType2     = rpcSimLink_ProcessType->at(vSimLink[iSimLink]);

                    if ( iSimLink == iSimLink2 ) continue; // To avoid self combinations
                    if ( iSimLink > iSimLink2) continue; // To avoid repeated combinations: "01" and "10"

                    if ( SimLinkRing == SimLinkRing2 && SimLinkSector == SimLinkSector2 && 
                    SimLinkStation == SimLinkStation2 && SimLinkLayer != SimLinkLayer2 ){
                        flag2LayerHit = true;
                        break;
                    } 
                }
                
                if(flag2LayerHit == false) continue;

                vTemp.push_back(vSimLink[iSimLink]);

                if (fdebug) std::cout << "iEvent " << iEvent << ", vSimLink2 " << vSimLink[iSimLink] << ", partID " << rpcSimLink_particleId->at(vSimLink[iSimLink]) 
                                    << " | " << "eta: "<< rpcSimLink_global_eta->at(vSimLink[iSimLink]) << " | phi: "<< rpcSimLink_global_phi->at(vSimLink[iSimLink])
                                    << " | " << "Wh: "<< SimLinkRing << " | Sec: "<< SimLinkSector << " | " << "St: "<< SimLinkStation
                                    << " | " << "Lay: "<< SimLinkLayer << " | Bx: "<< SimLinkBx << " | TrackID: "<< SimTrackID 
                                    << " | " << "ProType: "<< SimProType << std::endl;
            }
            vSimLink = vTemp;
            if (fdebug) std::cout << "vTemp.size(): "<< vTemp.size() << std::endl;
            vTemp.clear();
      
            for (int iSimLink = 0; iSimLink < vSimLink.size(); ++iSimLink) {
                
                Int_t SimLinkRing    = rpcSimLink_ring->at(vSimLink[iSimLink]);
                Int_t SimLinkSector  = rpcSimLink_sector->at(vSimLink[iSimLink]);
                Int_t SimLinkStation = rpcSimLink_station->at(vSimLink[iSimLink]);
                Int_t SimLinkLayer   = rpcSimLink_layer->at(vSimLink[iSimLink]);
                Int_t SimLinkBx      = rpcSimLink_bx->at(vSimLink[iSimLink]);

                if (SimLinkBx != 0) continue;

                if (fdebug) std::cout << "==============================================================================" << std::endl;
                if (fdebug) std::cout << "iSim " << iSimLink << ", iSimLink " << vSimLink[iSimLink] << ", partID " << rpcSimLink_particleId->at(vSimLink[iSimLink]) 
                                      << " | " << "eta: "<< rpcSimLink_global_eta->at(vSimLink[iSimLink]) << " | phi: "<< rpcSimLink_global_phi->at(vSimLink[iSimLink])
                                      << " | " << "Wh: "<< SimLinkRing << " | Sec: "<< SimLinkSector << " | " << "St: "<< SimLinkStation
                                      << " | " << "Lay: "<< SimLinkLayer << " | Bx: "<< SimLinkBx<< std::endl;
                // if (fdebug) std::cout << "\n" << std::endl;


                m_plots["hNSimLinkIdPDG"] -> Fill( rpcSimLink_particleId->at(vSimLink[iSimLink]));
                
                std::string chambTag = chambTags.at(SimLinkStation - 1);
                std::string whTag    = whTags.at(SimLinkRing + 2);
                std::string secTag   = secTags.at(SimLinkSector - 1);

                int wheelIdx = WheelStationToBins(SimLinkStation, SimLinkRing );
                m_plots["Eff_TPwheels_total"] -> Fill( wheelIdx );
                
                coutNrpcSimLink++;

                Int_t    bestTPidx = -999;
                Double_t bestTPtime = 999.;
                Double_t bestDeltaPhi = 999.;
                for (std::size_t iTrigAM = 0; iTrigAM < ph2TpgPhiEmuAm_nTrigs; ++iTrigAM){

                    Int_t trigAMWh  = ph2TpgPhiEmuAm_wheel->at(iTrigAM);
                    Int_t trigAMSec = ph2TpgPhiEmuAm_sector->at(iTrigAM);
                    Int_t trigAMSt  = ph2TpgPhiEmuAm_station->at(iTrigAM);
                    Int_t trigAMBX  = ph2TpgPhiEmuAm_BX->at(iTrigAM);
                    // Int_t trigAMqual = ph2TpgPhiEmuAm_quality->at(iTrigAM);
                    Int_t trigAMrpc  = ph2TpgPhiEmuAm_rpcFlag->at(iTrigAM);

                    if ( name == "RPCOnly" || name == "RPCOnlyUpdated" ) {
                        if ( trigAMrpc != 2 ) continue;
                    }
                    
                    // -----------------------------
                    // SimLink AND TP MATCHING
                    // -----------------------------
                    if (SimLinkRing == trigAMWh && SimLinkSector == trigAMSec && SimLinkStation  == trigAMSt ) {

                        if ( trigAMBX != 20 ) continue;

                        Double_t trigGlbPhi  = trigPhiInRad(ph2TpgPhiEmuAm_phi->at(iTrigAM),trigAMSec);
                        Double_t finalDPhi   = rpcSimLink_global_phi->at(vSimLink[iSimLink]) - trigGlbPhi;
                        Double_t trigSimDPhi = abs(acos(cos(finalDPhi)));
                        Double_t trigAMt0 = ph2TpgPhiEmuAm_t0->at(iTrigAM);
                            
                        // TODO: Check if we will apply a t0 cut
                        // if ( trigAMt0  < 500) continue;

                        trigAMt0 = (trigAMt0 * 25 / 32); // DCS to ns
                        trigAMt0 = trigAMt0 - 390; // Shift to zero (RPC only)

                        if (fdebug) std::cout << "  iTrigAM " << iTrigAM << " | trigAMWh: "<< trigAMWh  << " | trigAMSec: "
                                              << trigAMSec  << " | trigAMSt: "<< trigAMSt << " | phi: "<< trigGlbPhi 
                                              << " | trigSimDPhi: "<< trigSimDPhi << " | BX: "<< trigAMBX << " | t0: "<< trigAMt0  
                                              << std::endl;

                        // To select the best trigger if we have two or more in the same station.
                        // if (fdebug) std::cout << "       trigAMt0: " << trigAMt0 << " | bestTPtime: "<< bestTPtime << std::endl;
                        // if ( abs(trigAMt0) > abs(bestTPtime) ) continue;
                        // bestTPtime = trigAMt0;

                        if ( trigSimDPhi > bestDeltaPhi ) continue;
                        bestDeltaPhi = trigSimDPhi;
                        bestTPidx = iTrigAM;

                        m_plots["hSimLinkTPdeltaPhi"] -> Fill( trigSimDPhi );

                        // TODO: Check if we will apply a Delta phi cut
                        // if ( trigSimDPhi > 0.15) continue;

                    } // GEN AND TP MATCHING
                }// END loop Selected Trigger primitives

                if ( bestTPidx > -1 ){ // NUMERATOR
                        if (fdebug) std::cout << " bestTPidx: " << bestTPidx << std::endl;
                        // tpRPC_num++;
                        // bestTP.push_back(bestTPidx);
                        // vbestTPAM.push_back(bestTPidx);
                    
                        m_plots["Eff_TPwheels_matched"] -> Fill( wheelIdx );
                        // Efficiency TP by sector Numerator
                        // m_plots["Eff_TPwheels_"+secTag+"_matched"]->Fill(wheelIdx);
                        
                        Int_t trigAMBX = ph2TpgPhiEmuAm_BX->at(bestTPidx);
                        m_plots["hPh2TpgPhiEmuAmBX"+whTag+chambTag+"_matched"]->Fill(trigAMBX);
                        
                        Double_t trigAMt0 = ph2TpgPhiEmuAm_t0->at(bestTPidx);
                        trigAMt0 = (trigAMt0 * 25 / 32); // DCS to ns
                        trigAMt0 = trigAMt0 - 390; // Shift to zero (RPC only)

                        m_plots["hPh2TpgPhiEmuAmT0"+whTag+chambTag+"_matched"]->Fill(trigAMt0);
                }
                
            } // END Loop in the rpcSimLink

            m_plots["hNSimLinks"] -> Fill( rpcSimLink_nSimLinks );
            m_plots["hNSimLinksPDG13"] -> Fill( coutNrpcSimLink );
            
        }// END Loop Event

        // for (const auto & secTag : secTags)
        // {
        //     m_plots["fakeRate_EventWheelStationTP_"+secTag+"_matched"]->Scale(1.0 / nEntries);
        // }

        // -----------------------------------------------------------------
        // Creating directories to save control plots and root files
        // -----------------------------------------------------------------
        std::string outputDir = "output/"+name+"/";
        std::string histoDir  = "output/"+name+"/histograms/";
        std::string effDir    = "output/"+name+"/histograms/effPlots/";

        std::vector<std::string> v_outputDir;
        v_outputDir.push_back(outputDir);
        v_outputDir.push_back(histoDir);
        v_outputDir.push_back(effDir);
        for (const auto& outputDir : v_outputDir) {
            // Create the directory if it doesn't exist
            if (gSystem->AccessPathName(outputDir.c_str())) {
                gSystem->mkdir(outputDir.c_str(), true); // true = recursive
            }
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
        // Loop over the histogram map to save them in the root file and as png
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

        // Close the file (optional, as it will be automatically closed when outFile goes out of scope)
        outFile.Close();
        std::cout << "All histograms saved in ROOT file: " << outputFile << std::endl;
        std::cout << "All plots saved in: " << outputDir << std::endl;
    }

    std::cout << "----------------------------------" << std::endl;
    std::cout << "TEST FLAG: " << testFlag << std::endl;
    std::cout << "plotHistograms FLAG: " << plotHistograms << std::endl;
    std::cout << "----------------------------------" << std::endl;

    return 0;
}