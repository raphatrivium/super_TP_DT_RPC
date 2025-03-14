#include "super_TP_DT_RPC.h"



void test() {


    std::vector<std::string> file_names = { 
                                            // "input/DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_noRPC.root", 
                                            "input/DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_withRPC.root"    
                                            };

        

    for (size_t l = 0; l < file_names.size(); ++l) {

        std::string pathDqmRPCfile = file_names[l];
        std::cout << "-------------------------------------------" <<std::endl;
        std::cout << pathDqmRPCfile << "\n" <<std::endl;
        std::cout << "-------------------------------------------" <<std::endl;

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


        // ------------------------------------------------------------------------------
        // Loop in the events
        // ------------------------------------------------------------------------------

        nEntries = 100;   // 100   nEntries
        std::cout << "Total entries:" << nEntries <<std::endl;



        for (Long64_t i = 0; i < nEntries; ++i) { 

            tree->GetEntry(i);

            branch_gen_nGenParts->GetEntry(i);

            // -----------------------------
            // loop Gen Particle
            // -----------------------------
            for (int j = 0; j < gen_nGenParts; ++j) {


                // -----------------------------
                // Loop in the Segments (Reco Muons - Segments)
                // -----------------------------
                for (int k = 0; k < ph2Seg_nSegments; ++k) {

                    // -------------------------------------
                    // Segments quality selection
                    // -------------------------------------
                    if ( ph2Seg_phi_t0->at(k) > 15 || ph2Seg_phi_t0->at(k) < -15 ) continue; // time window
                    if ( ph2Seg_phi_nHits->at(k) < 4 ) continue; // at least 4 hits in the r-φ
                    // station 4 does not have r-z hits
                    if (ph2Seg_station->at(k) != 4 )
                        if (ph2Seg_z_nHits->at(k) < 4 ) continue; // at least 4 hits in the r-z

                    // -------------------------------------
                    // Delta R Calculation and Selection
                    // -------------------------------------
                    double deltaR = 0;
                    double deltaPhi = 0;
                    deltaR = deltaRfunction(gen_eta->at(j), gen_phi->at(j), ph2Seg_posGlb_eta->at(k), ph2Seg_posGlb_phi->at(k)) ;
                    if (deltaR > 0.2 ) continue;
                    
                }



            }


        }




    }

} // END Program