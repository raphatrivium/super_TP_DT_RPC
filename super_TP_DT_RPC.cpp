#include "super_TP_DT_RPC.h"



void super_TP_DT_RPC() {


    // std::vector<std::string> file_names = { "input/DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_noRPC.root" };

    // std::vector<std::string> file_names = { "input/DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_withRPC.root" };

    std::vector<std::string> file_names = { "input/DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_noRPC.root", 
                                            "input/DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_withRPC.root"    };

    // Loop input Files                                                    
    for (size_t l = 0; l < file_names.size(); ++l) {

        std::string pathDqmRPCfile = file_names[l];
        std::cout << "-------------------------------------------" <<std::endl;
        std::cout << pathDqmRPCfile << "\n" <<std::endl;
        std::cout << "-------------------------------------------" <<std::endl;

        // Create a new ROOT file for output
        TFile *file2 = new TFile("empty.root", "RECREATE");
        // tree = TTree("mytree", "mytreetitle");

        if ( l == 0)
            file2 = new TFile("output/DTDPGNtuple_histograms_noRPC.root", "RECREATE");
        else if ( l == 1)
            file2 = new TFile("output/DTDPGNtuple_histograms_withRPC.root", "RECREATE");

        // ---------------------------------
        // Open the ROOT file
        TFile *file = new TFile( (pathDqmRPCfile).c_str() );

        // ---------------------------------
        // Open TDirectoryFile
        TDirectoryFile *dir;
        dir = (TDirectoryFile*)file->Get( "dtNtupleProducer" );

        // ---------------------------------
        // Open Tree
        TTree *tree = (TTree*)dir->Get("DTTREE");
        Long64_t nEntries = tree->GetEntries();


        // ------------------------------------------------------------------
        // Variables
        // ------------------------------------------------------------------
        int testCounter = 0;

        // ------------------------------------------------------------------
        // Get Branch
        // ------------------------------------------------------------------

        // For int type
        // ------------
        TBranch *branch_event_bunchCrossing = tree->GetBranch("event_bunchCrossing");
        int event_bunchCrossing;
        branch_event_bunchCrossing->SetAddress(&event_bunchCrossing);

        TBranch *branch_event_orbitNumber = tree->GetBranch("event_orbitNumber");
        Long64_t event_orbitNumber;
        branch_event_orbitNumber->SetAddress(&event_orbitNumber);
        
        TBranch *branch_mu_nMuons = tree->GetBranch("mu_nMuons");
        int mu_nMuons;
        branch_mu_nMuons->SetAddress(&mu_nMuons);

        // For vector type
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
        std::vector<float> *ph2Seg_phiHits_superLayer = nullptr;
        tree->SetBranchAddress("ph2Seg_phiHits_superLayer", &ph2Seg_phiHits_superLayer);
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


        // ---------------------------------------------------------------------
        // Create a TH1F histogram
        // --------------------------------------------------------------------- 
        
        TH1F *histogram_event_bunchCrossing = new TH1F("histogram_event_bunchCrossing", "event_bunchCrossing", 100, -3, 3);

        // ------------------------------------------------------------------------------
        TH1F *histogram_gen_nGenParts = new TH1F("histogram_gen_nGenParts", "gen_nGenParts", 10, 0, 10); // Adjust the number of bins and range as needed
        TH1F *histogram_gen_pdgId = new TH1F("histogram_gen_pdgId", "gen_pdgId", 30, -15, 15);
        TH1F *histogram_gen_pt = new TH1F("histogram_gen_pt", "gen_pt", 100, 0, 200); 
        TH1F *histogram_gen_eta = new TH1F("histogram_gen_eta", "gen_eta", 100, -6, 6);
        TH1F *histogram_gen_phi = new TH1F("histogram_gen_phi", "gen_phi", 100, -6, 6);
        
        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_BX = new TH1F("histogram_ph2TpgPhiEmuAm_BX", "ph2TpgPhiEmuAm_BX", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_wheel = new TH1F("histogram_ph2TpgPhiEmuAm_wheel", "ph2TpgPhiEmuAm_wheel", 8, -4, 4);
        TH1F *histogram_ph2TpgPhiEmuAm_sector = new TH1F("histogram_ph2TpgPhiEmuAm_sector", "ph2TpgPhiEmuAm_sector", 15, 0, 15);
        TH1F *histogram_ph2TpgPhiEmuAm_station = new TH1F("histogram_ph2TpgPhiEmuAm_station", "ph2TpgPhiEmuAm_station", 5, 0, 5);

        TH1F *histogram_ph2TpgPhiEmuAm_quality = new TH1F("histogram_ph2TpgPhiEmuAm_quality", "ph2TpgPhiEmuAm_quality", 11, -2, 8);



        TH1F *histogram_ph2Tseg_phi_t0_Genmatched = new TH1F("histogram_ph2Tseg_phi_t0_Genmatched", "ph2Tseg_phi_t0_matched", 20, -10, 10);

        int nbins; 
        int minX; 
        int maX;
        // ------------------------------------------------------------------------------

        // DT Stations
        // ------------------------------------------------------------------------------
        // nbins=20; minX=-6; maX=50;
        nbins=20; minX=10; maX=30;
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);

        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);

        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);

        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);

        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4 = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4", "ph2TpgPhiEmuAm_BX", nbins, minX, maX);


        

        // DT Stations
        // ------------------------------------------------------------------------------
        // nbins=20; minX=10; maX=30;
        // nbins=20; minX=-6; maX=50;
        // nbins=40; minX=0; maX=40;
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        
        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);

        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);

        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);

        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched", "ph2TpgPhiEmuAm_BX_matched", nbins, minX, maX);


        // for numerator
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        
        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);

        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);

        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);

        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);
        TH1F *histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched_numerator = new TH1F("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched_numerator", "ph2TpgPhiEmuAm_BX_matched_numerator", 20, 10, 30);

        //-------------------------------------------------------------------
        //-------------- For Trigger primitive timing [ns]-----------------------
        //------------------------------------------------------------------
        nbins=27; minX=-10; maX=10;
        // nbins=50; minX=-10; maX=10;
        // int nbins=27; int minX=490; int maX=510;
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_1_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_1_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_2_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_2_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_3_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_3_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_4_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_4_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        
        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_1_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_1_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_2_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_2_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_3_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_3_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_4_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_4_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);

        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_1_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_1_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_2_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_2_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_3_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_3_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_4_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_4_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);

        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_1_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_1_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_2_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_2_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_3_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_3_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_4_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_4_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);

        // ------------------------------------------------------------------------------
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_1_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_1_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_2_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_2_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_3_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_3_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);
        TH1F *histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_4_matched = new TH1F("histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_4_matched", "ph2TpgPhiEmuAm_t0_matched", nbins, minX, maX);


        // ------------------------------------------------------------------------------
        // Loop in the events
        // ------------------------------------------------------------------------------

        nEntries = nEntries;   // 100   nEntries
        std::cout << "Total entries:" << nEntries <<std::endl;

        for (Long64_t i = 0; i < nEntries; ++i) { 

            tree->GetEntry(i);

            branch_event_bunchCrossing->GetEntry(i);
            histogram_event_bunchCrossing->Fill(event_bunchCrossing);

            branch_gen_nGenParts->GetEntry(i);
            histogram_gen_nGenParts->Fill(gen_nGenParts);

            branch_ph2Seg_nSegments->GetEntry(i);
            // histogram_ph2Seg_nSegments->Fill(ph2Seg_nSegments);

            // std::cout << "==============================================================================" << std::endl;
            // std::cout << "nGenParts: " << gen_nGenParts  << " | nSegments: " << ph2Seg_nSegments << " | nTP: " << ph2TpgPhiEmuAm_nTrigs <<std::endl;


            // -----------------------------
            // loop Gen Particle
            // -----------------------------
            std::vector<int> seg_matched_index;
            std::vector<double> seg_matched_DeltaR;
            for (int j = 0; j < gen_nGenParts; ++j) {
                // std::cout << "==============================================================================" << std::endl;
                // std::cout << "Entry " << i << ", Element " << j << "| " << "gen pt: "<< gen_pt->at(j) << " | " << "gen eta: "<< gen_eta->at(j) << " | gen phi: "<< gen_phi->at(j) << std::endl;
                // std::cout << "==============================================================================" << std::endl;
                // std::cout << "====================================================== Debug 1" << std::endl;

                if ( gen_pt->at(j) < 20. ) {
                    seg_matched_index.push_back(-99); // -99 indicates no match
                    seg_matched_DeltaR.push_back(-99);
                    continue;
                }

                histogram_gen_pdgId->Fill(gen_pdgId->at(j));
                histogram_gen_pt->Fill(gen_pt->at(j));
                histogram_gen_eta->Fill(gen_eta->at(j));
                histogram_gen_phi->Fill(gen_phi->at(j));


                // -----------------------------
                // Loop in the Segments (Reco Muons)
                // -----------------------------
                std::vector<double> DeltaR_values;
                std::vector<double> idx_DeltaR_values;
                for (int k = 0; k < ph2Seg_nSegments; ++k) {

                    double deltaR = 0.;

                    // -------------------------------------
                    // Segments quality selection
                    // -------------------------------------
                    // std::cout << " idx: " << k  << " | ph2Seg_phi_t0: " <<  ph2Seg_phi_t0->at(k) << std::endl;
                    if ( abs(ph2Seg_phi_t0->at(k)) > 15 ) continue; // time window

                    double muSegDPhi = abs(deltaPhifunction(gen_phi->at(j), ph2Seg_posGlb_phi->at(k))) ;
                    double muSegDEta = abs(gen_eta->at(j)-ph2Seg_posGlb_eta->at(k)) ;

                    if ( muSegDPhi > 0.1 ) continue;
                    if ( muSegDEta > 0.15 ) continue;
                    if ( ph2Seg_phi_nHits->at(k) < 4 ) continue; // at least 4 hits in the r-φ
                    // station 4 does not have r-z hits
                    if (ph2Seg_station->at(k) != 4 )
                        if (ph2Seg_z_nHits->at(k) < 4 ) continue; // at least 4 hits in the r-z

                    deltaR = deltaRfunction(gen_eta->at(j), gen_phi->at(j), ph2Seg_posGlb_eta->at(k), ph2Seg_posGlb_phi->at(k)) ;

                    // deltaPhi = deltaPhifunction(gen_phi->at(j), ph2Seg_posGlb_phi->at(k)) ;
                    // std::cout << " idx: " << k  << " | deltaR: " <<  deltaR << " | muSegDPhi: " <<  muSegDPhi << " | muSegDEta: " 
                    // <<  muSegDEta << std::endl;

                    DeltaR_values.push_back(deltaR);
                    idx_DeltaR_values.push_back(k);
                    
                }

                int minIndex;
                double minElement;
                if (!DeltaR_values.empty()) { // Check if the vector is not empty to avoid undefined behavior

                    // Find the iterator to the minimum element in the vector
                    auto minElementIter = std::min_element(DeltaR_values.begin(), DeltaR_values.end());
                    // Calculate the index of the minimum element
                    minIndex = std::distance(DeltaR_values.begin(), minElementIter);
                    minElement = *minElementIter;

                    // std::cout << "Minimum element: " << *minElementIter << " | Index: " << minIndex << " | General Index: " << idx_DeltaR_values[minIndex]  << std::endl;
                }
                else {
                    seg_matched_index.push_back(-99); // -99 indicates no match
                    seg_matched_DeltaR.push_back(-99);
                    continue;
                }

                // Check if the TP was already used. 
                // If yes, try to check which one has lower DeltaR velue
                int value_to_find = idx_DeltaR_values[minIndex];
                auto it = std::find(seg_matched_index.begin(), seg_matched_index.end(), value_to_find);

                if (it != seg_matched_index.end()) { // If the value_to_find was founded do...

                    // std::cout << "Value " << value_to_find << " exists in the vector." << std::endl;

                    // Calculate the index from the iterator
                    int index = std::distance(seg_matched_index.begin(), it);

                    if ( seg_matched_DeltaR[index] < DeltaR_values[ minIndex ]  ){
                        seg_matched_index.push_back(-99);
                        seg_matched_DeltaR.push_back(-99);
                    }
                    else{
                        seg_matched_index[index] = -99;
                        seg_matched_DeltaR[index] = -99;
                        seg_matched_index.push_back(idx_DeltaR_values[minIndex]);
                        seg_matched_DeltaR.push_back(DeltaR_values[ minIndex ]);
                    }
                } 
                else {
                    seg_matched_index.push_back(idx_DeltaR_values[minIndex]);
                    seg_matched_DeltaR.push_back(DeltaR_values[ minIndex ]);
                }
                


            } // END loop Gen Particle

            // std::cout << "-----------------------------" << std::endl;
            // std::cout << " After GEN Matching" << std::endl;
            // std::cout << "-----------------------------" << std::endl;
            for (size_t k = 0; k < seg_matched_index.size(); ++k) {
            
                double deltaR;
                double deltaPhi;
                double seg_mat_t0;

                if ( seg_matched_index[k] == -99) {
                    deltaR = -99;
                    deltaPhi = -99;
                    seg_mat_t0 = -99;
                }
                else{
                    deltaR = deltaRfunction(gen_eta->at(k), gen_phi->at(k), ph2Seg_posGlb_eta->at(seg_matched_index[k]),
                                            ph2Seg_posGlb_phi->at(seg_matched_index[k])) ;
                    deltaPhi = deltaPhifunction(gen_phi->at(k), ph2Seg_posGlb_phi->at(seg_matched_index[k])) ;

                    seg_mat_t0 = ph2Seg_phi_t0->at(seg_matched_index[k]);
                    histogram_ph2Tseg_phi_t0_Genmatched->Fill(seg_mat_t0);
                }
                
                // std::cout << "mu: " << k  << " | seg_idx: " << seg_matched_index[k] << " | deltaR: " <<  deltaR << " | deltaPhi: " <<  deltaPhi << " | seg_mat_t0: " <<  seg_mat_t0 << std::endl;

            }

            // -----------------------------
            // Loop in the Matched Segments AM For TP matching
            // -----------------------------
            std::vector<int> tp_matched_index; // Vector with the index of the TP matching with Segments
            std::vector<float> tp_matched_posLoc_x; // auxiliar vector

            for (size_t j = 0; j < seg_matched_index.size(); ++j) {

                if ( seg_matched_index[j] == -99) {
                    tp_matched_index.push_back(-99); // -99 indicates no match 
                    tp_matched_posLoc_x.push_back(-99);
                    continue;
                } 

                std::vector<double> posLoc_x_values;
                std::vector<int> idx_x_values;
                // std::cout << " ---------: " <<  std::endl;
                for (int k = 0; k < ph2TpgPhiEmuAm_nTrigs; ++k) {

                    // if ( ph2TpgPhiEmuAm_BX->at(k) < 18 ) continue; // time window
                    // if ( ph2TpgPhiEmuAm_BX->at(k) > 22 ) continue; // time window

                    if ( ph2Seg_wheel->at(seg_matched_index[j]) != ph2TpgPhiEmuAm_wheel->at(k) ) continue;
                    if ( ph2Seg_station->at(seg_matched_index[j]) != ph2TpgPhiEmuAm_station->at(k) ) continue;

                    posLoc_x_values.push_back( abs(ph2TpgPhiEmuAm_posLoc_x->at(k)) );
                    idx_x_values.push_back(k);
                }

                // tp_matched_index
                int minIndex;
                double minElement;
                if (!posLoc_x_values.empty()) { // Check if the vector is not empty to avoid undefined behavior

                    // Find the iterator to the minimum element in the vector
                    auto minElementIter = std::min_element(posLoc_x_values.begin(), posLoc_x_values.end());
                    // Calculate the index of the minimum element
                    minIndex = std::distance(posLoc_x_values.begin(), minElementIter);
                    minElement = *minElementIter;

                    // std::cout << "Minimum element: " << *minElementIter << " | Index: " << minIndex << " | General Index: " << idx_x_values[minIndex]  << std::endl;
                   
                }
                else {
                    tp_matched_index.push_back(-99); // -99 indicates no match 
                    tp_matched_posLoc_x.push_back(-99);
                    continue;
                }
                
                // // Check if the TP was already used. If yes, try to check which one has better matching following de DeltaR velue
                int value_to_find = idx_x_values[minIndex];
                auto it = std::find(tp_matched_index.begin(), tp_matched_index.end(), value_to_find);

                if (it != tp_matched_index.end()) {

                    // std::cout << "Value " << value_to_find << " exists in the vector." << std::endl;

                    // Calculate the index from the iterator
                    int index = std::distance(tp_matched_index.begin(), it);

                    if ( tp_matched_posLoc_x[index] < posLoc_x_values[ minIndex ]  ){
                        tp_matched_index.push_back(-99);
                        tp_matched_posLoc_x.push_back(-99);
                    }
                    else{
                        tp_matched_index[index] = -99;
                        tp_matched_posLoc_x[index] = -99;
                        tp_matched_index.push_back(idx_x_values[minIndex]);
                        tp_matched_posLoc_x.push_back(posLoc_x_values[ minIndex ]);
                    }
                } 
                else {
                    tp_matched_index.push_back(idx_x_values[minIndex]);
                    tp_matched_posLoc_x.push_back(posLoc_x_values[ minIndex ]);
                }
            
            } // END Loop in the TP AM      For matching

            // std::cout << "-----------------------------" << std::endl;
            // std::cout << " After TP Matching" << std::endl;
            // std::cout << "-----------------------------" << std::endl;
            for (size_t k = 0; k < tp_matched_index.size(); ++k) {
                double tp_mat_posLoc_x;
                double tp_mat_BX;
                double tp_mat_t0;

                if ( tp_matched_index[k] == -99) {
                    tp_mat_posLoc_x = -99;
                    tp_mat_BX = -99;
                    tp_mat_t0 = -9999;
                }
                else{
                    tp_mat_posLoc_x = ph2TpgPhiEmuAm_posLoc_x->at(tp_matched_index[k]);
                    tp_mat_BX = ph2TpgPhiEmuAm_BX->at(tp_matched_index[k]);
                    tp_mat_t0 = ph2TpgPhiEmuAm_t0->at(tp_matched_index[k]);
                    // histogram_ph2Tseg_phi_t0_Genmatched->Fill(seg_mat_t0);
                }
                
                // std::cout << "mu: " << k  << " | tp_idx: " << tp_matched_index[k] << " | posLoc_x: " <<  tp_mat_posLoc_x << " | tp_mat_BX: " << tp_mat_BX << " | tp_mat_t0: " << tp_mat_t0 << std::endl;

            }
            
            // --------------------------------------------------
            // updating the vectors
            // --------------------------------------------------
            for (size_t k = 0; k < tp_matched_posLoc_x.size(); ++k) {
                if ( tp_matched_posLoc_x[k] == -99 ){
                    seg_matched_index[k] = -99;
                    seg_matched_DeltaR[k] = -99;
                }
            }
            

            // -----------------------------
            // Loop for efficiency
            // -----------------------------       

            for (size_t k = 0; k < tp_matched_index.size(); ++k) {

                if (  tp_matched_index[k] == -99 ) continue;

                int wheel_idx = ph2TpgPhiEmuAm_wheel->at( tp_matched_index[k] );
                int station_idx = ph2TpgPhiEmuAm_station->at( tp_matched_index[k] );
                double tp_BX = ph2TpgPhiEmuAm_BX->at( tp_matched_index[k] );
                double tp_t0 = ph2TpgPhiEmuAm_t0->at( tp_matched_index[k] );

                // std::cout << "tp_BX: " << tp_BX  << " | tp_t0: " << tp_t0 << std::endl;


                if ( tp_BX < 18  || tp_BX > 22 ) continue;


                std::vector<double> shif_correction;
                if ( file_names[l] == "input/DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_noRPC.root" )
                    shif_correction = {500.858, 501.358, 500.444, 498.841, 500.159, 500.875, 501.609, 499.932, 499.884, 500.906, 500.812, 498.754, 499.847, 500.394, 501.533, 499.636, 500.708, 501.118, 500.373, 499.091};
                if ( file_names[l] == "input/DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_withRPC.root" )
                    shif_correction = {499.873, 499.408, 500, 499.346, 499.762, 499.566, 500.336, 499.822, 499.643, 499.546, 499.6, 499.351, 499.537, 499.66, 500.151, 499.849, 499.887, 499.321, 499.796, 499.507};

                // shif_correction = {500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500};

                // if ( file_names[l] == "input/DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_noRPC.root" )
                //     shif_correction = {500.858, 501.358, 500.444, 498.841, 500.159, 500.875, 501.609, 499.932, 499.884, 500.906, 500.812, 498.754, 499.847, 500.394, 501.533, 499.636, 500.708, 501.118, 500.373, 499.091};
                // if ( file_names[l] == "input/DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_withRPC.root" )
                //     shif_correction = {499.873, 499.408, 500, 499.346, 499.762, 499.566, 500.336, 499.822, 499.643, 499.546, 499.6, 499.351, 499.537, 499.66, 500.151, 499.849, 499.887, 499.321, 499.796, 499.507};

                if ( wheel_idx == -2 && station_idx == 1 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_1_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[0] ));}
                if ( wheel_idx == -2 && station_idx == 2 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched->Fill( tp_BX );
                     histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_2_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[1] ));}
                if ( wheel_idx == -2 && station_idx == 3 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_3_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[2] ));}
                if ( wheel_idx == -2 && station_idx == 4 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_4_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[3] ));}

                if ( wheel_idx == -1 && station_idx == 1 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_1_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[4] ));}
                if ( wheel_idx == -1 && station_idx == 2 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_2_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[5] ));}
                if ( wheel_idx == -1 && station_idx == 3 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched->Fill( tp_BX );
                     histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_3_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[6] ));}
                if ( wheel_idx == -1 && station_idx == 4 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_4_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[7] ));}

                if ( wheel_idx == 0 && station_idx == 1 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_1_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[8] ));}
                if ( wheel_idx == 0 && station_idx == 2 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_2_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[9] ));}
                if ( wheel_idx == 0 && station_idx == 3 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_3_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[10] ));}
                if ( wheel_idx == 0 && station_idx == 4 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_4_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[11] ));}

                if ( wheel_idx == 1 && station_idx == 1 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched->Fill( tp_BX );
                     histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_1_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[12] ));}
                if ( wheel_idx == 1 && station_idx == 2 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_2_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[13] ));}
                if ( wheel_idx == 1 && station_idx == 3 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_3_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[14] ));}
                if ( wheel_idx == 1 && station_idx == 4 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_4_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[15] ));}
                
                if ( wheel_idx == 2 && station_idx == 1 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_1_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[16] ));}
                if ( wheel_idx == 2 && station_idx == 2 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_2_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[17] ));}
                if ( wheel_idx == 2 && station_idx == 3 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_3_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[18]) );}
                if ( wheel_idx == 2 && station_idx == 4 ){
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched->Fill( tp_BX );
                    histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_4_matched->Fill( (tp_t0 * 25 / 32) - round(shif_correction[19] ));}

                // -----------------------------------------
                // Numerator
                // -----------------------------------------
                double deltaPhi = deltaPhifunction( gen_phi->at(k) , ph2Seg_posGlb_phi->at(seg_matched_index[k]) );

                // std::cout << "deltaPhi: " << abs(deltaPhi) << "  |  gen_phi: " << gen_phi->at(k) << " |  ph2Seg_posGlb_phi: "  <<  ph2Seg_posGlb_phi->at(seg_matched_index[k]) << std::endl ;

                // if ( abs(deltaPhi) > 0.1 ) continue;

                if ( tp_BX < 19  || tp_BX > 21 ) continue;

                // if ( tp_BX !=20 ) continue;


        
                if ( wheel_idx == -2 && station_idx == 1 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched_numerator->Fill( tp_BX );
                if ( wheel_idx == -2 && station_idx == 2 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched_numerator->Fill( tp_BX );
                if ( wheel_idx == -2 && station_idx == 3 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched_numerator->Fill( tp_BX );
                if ( wheel_idx == -2 && station_idx == 4 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched_numerator->Fill( tp_BX );

                if ( wheel_idx == -1 && station_idx == 1 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched_numerator->Fill( tp_BX );
                if ( wheel_idx == -1 && station_idx == 2 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched_numerator->Fill( tp_BX );
                if ( wheel_idx == -1 && station_idx == 3 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched_numerator->Fill( tp_BX );
                if ( wheel_idx == -1 && station_idx == 4 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched_numerator->Fill( tp_BX );

                if ( wheel_idx == 0 && station_idx == 1 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched_numerator->Fill( tp_BX );
                if ( wheel_idx == 0 && station_idx == 2 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched_numerator->Fill( tp_BX );
                if ( wheel_idx == 0 && station_idx == 3 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched_numerator->Fill( tp_BX );
                if ( wheel_idx == 0 && station_idx == 4 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched_numerator->Fill( tp_BX );

                if ( wheel_idx == 1 && station_idx == 1 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched_numerator->Fill( tp_BX );
                if ( wheel_idx == 1 && station_idx == 2 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched_numerator->Fill( tp_BX );
                if ( wheel_idx == 1 && station_idx == 3 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched_numerator->Fill( tp_BX );
                if ( wheel_idx == 1 && station_idx == 4 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched_numerator->Fill( tp_BX );
                
                if ( wheel_idx == 2 && station_idx == 1 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched_numerator->Fill( tp_BX );
                if ( wheel_idx == 2 && station_idx == 2 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched_numerator->Fill( tp_BX );
                if ( wheel_idx == 2 && station_idx == 3 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched_numerator->Fill( tp_BX );
                if ( wheel_idx == 2 && station_idx == 4 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched_numerator->Fill( tp_BX );



            }



            // -----------------------------
            // Loop in the TP AM
            // -----------------------------
            for (int j = 0; j < ph2TpgPhiEmuAm_nTrigs; ++j) {
                histogram_ph2TpgPhiEmuAm_BX->Fill(ph2TpgPhiEmuAm_BX->at(j));
                histogram_ph2TpgPhiEmuAm_wheel->Fill(ph2TpgPhiEmuAm_wheel->at(j));
                histogram_ph2TpgPhiEmuAm_sector->Fill(ph2TpgPhiEmuAm_sector->at(j));
                histogram_ph2TpgPhiEmuAm_station->Fill(ph2TpgPhiEmuAm_station->at(j));
               
                int wheel_idx = ph2TpgPhiEmuAm_wheel->at(j);
                int station_idx = ph2TpgPhiEmuAm_station->at(j);
                double tp_BX = ph2TpgPhiEmuAm_BX->at(j);

                if ( wheel_idx == -2 && station_idx == 1 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1->Fill(tp_BX);
                if ( wheel_idx == -2 && station_idx == 2 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2->Fill(tp_BX);
                if ( wheel_idx == -2 && station_idx == 3 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3->Fill(tp_BX);
                if ( wheel_idx == -2 && station_idx == 4 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4->Fill(tp_BX);

                if ( wheel_idx == -1 && station_idx == 1 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1->Fill(tp_BX);
                if ( wheel_idx == -1 && station_idx == 2 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2->Fill(tp_BX);
                if ( wheel_idx == -1 && station_idx == 3 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3->Fill(tp_BX);
                if ( wheel_idx == -1 && station_idx == 4 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4->Fill(tp_BX);

                if ( wheel_idx == 0 && station_idx == 1 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1->Fill(tp_BX);
                if ( wheel_idx == 0 && station_idx == 2 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2->Fill(tp_BX);
                if ( wheel_idx == 0 && station_idx == 3 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3->Fill(tp_BX);
                if ( wheel_idx == 0 && station_idx == 4 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4->Fill(tp_BX);

                if ( wheel_idx == 1 && station_idx == 1 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1->Fill(tp_BX);
                if ( wheel_idx == 1 && station_idx == 2 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2->Fill(tp_BX);
                if ( wheel_idx == 1 && station_idx == 3 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3->Fill(tp_BX);
                if ( wheel_idx == 1 && station_idx == 4 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4->Fill(tp_BX);
                
                if ( wheel_idx == 2 && station_idx == 1 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1->Fill(tp_BX);
                if ( wheel_idx == 2 && station_idx == 2 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2->Fill(tp_BX);
                if ( wheel_idx == 2 && station_idx == 3 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3->Fill(tp_BX);
                if ( wheel_idx == 2 && station_idx == 4 )
                    histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4->Fill(tp_BX);
                
            }

         
            // ---------------------------------------------------
            // Calculate and print progress every 1000 iterations
            // ---------------------------------------------------
            if (i % 500 == 0) {
                double percentage = (double)i / nEntries;
                printProgress(percentage);
            }
            
        }


        bool makehistograms = false;  // true    -    false

        // Draw the histogram
        TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600);

        // ---------------------------------------------------
        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_gen_nGenParts->Draw();
        canvas->SaveAs("histograms/histogram_gen_nGenParts.png");
        file2->WriteObject(histogram_gen_nGenParts, "histogram_gen_nGenParts");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_gen_pdgId->Draw();
        canvas->SaveAs("histograms/histogram_gen_pdgId.png");
        file2->WriteObject(histogram_gen_pdgId, "histogram_gen_pdgId");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_gen_pt->Draw();
        canvas->SaveAs("histograms/histogram_gen_pt.png");
        file2->WriteObject(histogram_gen_pt, "histogram_gen_pt");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_gen_eta->Draw();
        canvas->SaveAs("histograms/histogram_gen_eta.png");
        file2->WriteObject(histogram_gen_eta, "histogram_gen_eta");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_gen_phi->Draw();
        canvas->SaveAs("histograms/histogram_gen_phi.png");
        file2->WriteObject(histogram_gen_phi, "histogram_gen_phi");
        
        // ---------------------------------------------------
        
        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2Tseg_phi_t0_Genmatched->Draw();
        canvas->SaveAs("histograms/histogram_ph2Tseg_phi_t0_Genmatched.png");
        file2->WriteObject(histogram_ph2Tseg_phi_t0_Genmatched, "histogram_ph2Tseg_phi_t0_Genmatched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4");


        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched_numerator->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched_numerator.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched_numerator, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched_numerator");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_1_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_1_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_1_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_1_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_2_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_2_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_2_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_2_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_3_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_3_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_3_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_3_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_4_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_4_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_4_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_4_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_1_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_1_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_1_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_1_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_2_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_2_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_2_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_2_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_3_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_3_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_3_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_3_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_4_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_4_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_4_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_4_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_1_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_1_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_1_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_1_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_2_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_2_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_2_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_2_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_3_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_3_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_3_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_3_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_4_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_4_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_4_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_4_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_1_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_1_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_1_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_1_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_2_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_2_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_2_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_2_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_3_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_3_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_3_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_3_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_4_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_4_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_4_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_4_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_1_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_1_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_1_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_1_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_2_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_2_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_2_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_2_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_3_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_3_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_3_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_3_matched");

        canvas = new TCanvas("canvas", "Canvas", 800, 600);
        histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_4_matched->Draw();
        canvas->SaveAs("histograms/ph2TpgThetaEmuAm/histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_4_matched.png");
        file2->WriteObject(histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_4_matched, "histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_4_matched");



        // Efficiency
        double nume = 0.;
        double deno = 0.;
        double effi = 0.;


        std::cout << "----------------------------------------------" << std::endl;
        std::cout << "-----------      Efficnecy      --------------" << std::endl;
        std::cout << "----------------------------------------------" << std::endl;
        
        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W-2 MB1: " << effi << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W-2 MB2: " << effi << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W-2 MB3: " << effi << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W-2 MB4: " << effi << std::endl;

        std::cout << "----------------------------------------------" << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W-1 MB1: " << effi << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi  W-1 MB2: " << effi << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi  W-1 MB3: " << effi << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi  W-1 MB4: " << effi << std::endl;


        std::cout << "----------------------------------------------" << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W0 MB1: " << effi << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W0 MB2: " << effi << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W0 MB3: " << effi << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W0 MB4: " << effi << std::endl;

        std::cout << "----------------------------------------------" << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W+1 MB1: " << effi << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched->GetEntries();
        effi = nume/deno;
        std::cout << "  nume W+1 MB2: " << nume << std::endl;
        std::cout << "  deno W+1 MB2: " << deno << std::endl;
        std::cout << "effi W+1 MB2: " << effi << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W+1 MB3: " << effi << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W+1 MB4: " << effi << std::endl;

        std::cout << "----------------------------------------------" << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W+2 MB1: " << effi << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W+2 MB2: " << effi << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W+2 MB3: " << effi << std::endl;

        nume =  histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched_numerator->GetEntries();
        deno =  histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched->GetEntries();
        effi = nume/deno;
        std::cout << "effi W+2 MB4: " << effi << std::endl;


        std::cout << " \n \n \n" << std::endl;

        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_1_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_2_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_3_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_4_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_1_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_2_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_3_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_4_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_1_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_2_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_3_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_4_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_1_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_2_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_3_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_4_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_1_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_2_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_3_matched->GetMean() << std::endl;
        // std::cout << histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_4_matched->GetMean() << std::endl;
 

        file->Close();
        delete file;

        // Close the file
        file2->Close();

    } // END Loop files
    

    std::cout << "--------------------------------" << std::endl;
    std::cout << "END PROGRAM" << std::endl;
    std::cout << "--------------------------------" << std::endl;

}

void list_branches() {

    // Open the ROOT file
    TFile *file = TFile::Open("DTDPGNtuple_11_1_0_patch2_Phase2_Simulation.root");

    if (!file || file->IsZombie()) {
        std::cerr << "Failed to open the file!" << std::endl;
        // return 1;
    }

    // Open TDirectoryFile
    TDirectoryFile *dir;
    dir = (TDirectoryFile*)file->Get( "dtNtupleProducer" );

    // Access the TTree
    TTree *tree = (TTree*)dir->Get("DTTREE");

    if (!tree) {
        std::cerr << "Tree not found!" << std::endl;
        file->Close();
        // return 1;
    }

    // Get the list of branches
    TObjArray *branchList = tree->GetListOfBranches();
    TIter next(branchList);
    TBranch *branch;

    while ((branch = (TBranch*)next())) {
        // Get the branch name
        std::string branchName = branch->GetName();

        // Print the branch information
        std::cout << "Branch: " << branchName << std::endl;

        // Get the first leaf of the branch
        TLeaf *leaf = branch->GetLeaf(branchName.c_str());

        if (leaf) {
            // Print the type of the branch
            std::cout << "Type: " << leaf->GetTypeName() << std::endl;
        } else {
            std::cout << "No leaf found for branch: " << branchName << std::endl;
        }

        std::cout << "--------------------------------" << std::endl;
    }

    // Clean up
    file->Close();
    delete file;

}

