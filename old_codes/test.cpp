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

        nEntries = 10;   // 100   nEntries
        std::cout << "Total entries:" << nEntries <<std::endl;



        for (Long64_t iEvent = 0; iEvent < nEntries; ++iEvent) { 

            tree->GetEntry(iEvent);

            branch_gen_nGenParts->GetEntry(iEvent);

            // -----------------------------
            // loop Gen Particle
            // -----------------------------
            for (int iGen = 0; iGen < gen_nGenParts; ++iGen) {

                std::cout << "==============================================================================" << std::endl;
                std::cout << "iEvent " << iEvent << ", iGen " << iGen << " | " << "gen pt: "<< gen_pt->at(iGen) << " | " << "gen eta: "<< gen_eta->at(iGen) << " | gen phi: "<< gen_phi->at(iGen) << std::endl;
                std::cout << "==============================================================================" << std::endl;

                // pT Selection
                if ( gen_pt->at(iGen) < 20. ) continue;


                // -----------------------------
                // Loop in the Segments (Reco Muons)
                // -----------------------------
                std::vector<double> segDeltaR;
                std::vector<double> idx_segDeltaR;
                for (int iSeg = 0; iSeg < ph2Seg_nSegments; ++iSeg) {

                    double deltaR = 0.;

                    // -------------------------------------
                    // Segments quality selection
                    // -------------------------------------
                    // std::cout << " idx: " << iSeg  << " | ph2Seg_phi_t0: " <<  ph2Seg_phi_t0->at(k) << std::endl;
                    if ( abs(ph2Seg_phi_t0->at(iSeg)) > 15 ) continue; // time window

                    double muSegDPhi = abs(deltaPhifunction(gen_phi->at(iGen), ph2Seg_posGlb_phi->at(iSeg))) ;
                    double muSegDEta = abs(gen_eta->at(iGen)-ph2Seg_posGlb_eta->at(iSeg)) ;

                    if ( muSegDPhi > 0.1 ) continue;
                    if ( muSegDEta > 0.15 ) continue;
                    if ( ph2Seg_phi_nHits->at(iSeg) < 4 ) continue; // at least 4 hits in the r-φ
                    // station 4 does not have r-z hits
                    if (ph2Seg_station->at(iSeg) != 4 )
                        if (ph2Seg_z_nHits->at(iSeg) < 4 ) continue; // at least 4 hits in the r-z


                    // std::cout << "Seg " << iSeg << std::endl;


                    deltaR = deltaRfunction(gen_eta->at(iGen), gen_phi->at(iGen), ph2Seg_posGlb_eta->at(iSeg), ph2Seg_posGlb_phi->at(iSeg)) ;

                    segDeltaR.push_back(deltaR);
                    idx_segDeltaR.push_back(iSeg);
                    
                }

                // Print elements of the vector
                for (size_t iElemt = 0; iElemt < segDeltaR.size(); ++iElemt) {
                    std::cout << segDeltaR[iElemt] << " ";
                }
                std::cout << std::endl;
                // Print elements of the vector
                for (size_t iElemt = 0; iElemt < idx_segDeltaR.size(); ++iElemt) {
                    std::cout << idx_segDeltaR[iElemt] << " ";
                }
                std::cout << std::endl;


                for (size_t iElemt = 0; iElemt < idx_segDeltaR.size(); ++iElemt) {


                    for (int iTrigAM = 0; iTrigAM < ph2TpgPhiEmuAm_nTrigs; ++iTrigAM){
                    
                        // std::cout << "iTrigAM: " << iTrigAM << " | Tpt0: "  << ph2TpgPhiEmuAm_t0->at(iTrigAM)  << std::endl;
    
                        
    
    
    
                    }
                    
                }

                

            }


        }




    }

} // END Program