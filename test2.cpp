// This code is a modificated version file to run locally of the DTNtupleTPGSimAnalyzer_Efficiency.cpp 
// that can be found in the github: 
// https://github.com/jaimeleonh/DTNtuples/blob/unifiedPerf/test/DTNtupleTPGSimAnalyzer_Efficiency.C


#include "DTNtupleTPGSimAnalyzer.h"

int test2() { // 

    bool testFlag = false;   // false - true
    bool fdebug = false;

    bool plotHistograms = true; // false - true

    // ------------------------------------------------------------------------------
    // INPUT FILES
    // ------------------------------------------------------------------------------
    std::string inputDir = "input/";
    std::map<std::string,std::string> m_files;
    m_files["DTAM"]              = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_step2_noRPC.root";
    m_files["RPC"]               = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_step2_RPC.root";
    
    // m_files["DTAM"]              = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_noRPC_1Event.root";
    // m_files["RPC"]               = "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_RPC_1Event.root";
    m_files["test"]         = "test.root"; // It is a copy of m_files["RPC"]

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

        // ---------------------------------------
        // Making Map of Histograms 
        // ---------------------------------------
    

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

        // ---------------------------------
        // Branching Adressing
        // ---------------------------------
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

        // ------------------------------------------------------------------------------
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

        // ------------------------------------------------------------------------------
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
        
        // ------------------------------------------------------------------------------
        // Quality Selection Cuts
        // ------------------------------------------------------------------------------
        double m_minMuPt = 20;
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

        // ------------------------------------------------------------------------------
        // Control Variables
        // ------------------------------------------------------------------------------
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
        nEntries = 1;   // 100   nEntries
        if (testFlag){
            nEntries = 100;
            std::cout << "FOR TESTE:" <<std::endl;
        }
        std::cout << "Total entries:" << nEntries <<std::endl;

        int idxGen = 0;
        for (Long64_t iEvent = 0; iEvent < nEntries; ++iEvent) { 

            tree->GetEntry(iEvent);

            std::cout << "==============================================================================" << std::endl;
            std::cout << "iEvent " << iEvent << std::endl;
            std::cout << "==============================================================================" << std::endl;
        
            // -----------------------------
            // Loop in the AM TP
            // -----------------------------
            std::cout << "      Loop in the AM TP " << std::endl;
            std::cout << "      Total number of TP in this event: "<< ph2TpgPhiEmuAm_nTrigs << std::endl;  
            // for (std::size_t iTrigAM = 0; iTrigAM < ph2TpgPhiEmuAm_nTrigs; ++iTrigAM){
            for (std::size_t iTrigAM = 0; iTrigAM < 30; ++iTrigAM){ // For test

                Int_t trigAMWh   = ph2TpgPhiEmuAm_wheel->at(iTrigAM);
                Int_t trigAMSec  = ph2TpgPhiEmuAm_sector->at(iTrigAM);
                Int_t trigAMSt   = ph2TpgPhiEmuAm_station->at(iTrigAM);
                Int_t trigAMBX   = ph2TpgPhiEmuAm_BX->at(iTrigAM);
                Int_t trigAMqual = ph2TpgPhiEmuAm_quality->at(iTrigAM);
                Double_t trigAMt0   = ph2TpgPhiEmuAm_t0->at(iTrigAM);
                Int_t trigAMrpc  = ph2TpgPhiEmuAm_rpcFlag->at(iTrigAM);

                if ( trigAMrpc != 0 && trigAMrpc != 1) continue; // To avoid RPC only segments

                std::cout << " iTrigAM: " << iTrigAM << " | Wheel: "<< trigAMWh << " | Sector: " << trigAMSec << " | Station: " << trigAMSt << " | BX: " << trigAMBX << " | t0: " << trigAMt0  <<  " | Flag: " << trigAMrpc << std::endl;

            }

        }
    }

    return 0;
}