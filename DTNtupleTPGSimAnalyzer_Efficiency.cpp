// This code is a modificated version file to run locally of the DTNtupleTPGSimAnalyzer_Efficiency.cpp 
// that can be found in the github: 
// https://github.com/jaimeleonh/DTNtuples/blob/unifiedPerf/test/DTNtupleTPGSimAnalyzer_Efficiency.C


#include "DTNtupleTPGSimAnalyzer.h"

void DTNtupleTPGSimAnalyzer_Efficiency() {

    bool testFlag = false;   // false  -   true

    // ------------------------------------------------------------------------------
    // INPUT FILES
    // ------------------------------------------------------------------------------
    std::string inputDir = "input/";
    // std::vector<std::string> file_names  = {"DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_step2_noRPC.root", 
    //                                         "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_step2_RPC.root"};

    std::vector<std::string> file_names  = {"DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_step2_noRPC_updated.root", 
                                            "DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_step2_RPC_updated.root"};

    if (testFlag) file_names  = {"DTDPGNtuple_11_1_0_patch2_Phase2_Simulation_step2_RPC.root"};

    for (const auto & file_name : file_names)
    {                                 
        
        std::cout << "-------------------------------------------" <<std::endl;
        std::cout << inputDir+file_name << "\n" <<std::endl;
        std::cout << "-------------------------------------------" <<std::endl;
        
        // ---------------------------------------
        // Making Map of Histograms 
        // ---------------------------------------
        std::map<std::string, TH1*> m_plots;
        std::map<std::string, TH2*> m_plots2;
        std::map<std::string, TEfficiency*> m_effs;

        std::vector<std::string> algoTag  = {"AM", "AM+RPC", "Ph1"};
        std::vector<std::string> totalTag = {"matched", "total"};
        std::vector<std::string> chambTag = {"MB1",     "MB2", "MB3", "MB4"};
        std::vector<std::string> wheelTag = {"Wh.-2","Wh.-1","Wh.0","Wh.+1","Wh.+2",};

        m_plots["hNTrigs"] = new TH1D("hNTrigs", "Number of Triggers ; Number of Triggers; Entries", 50, 0, 300);

        m_plots["hGenSegments"] = new TH1D("hGenSegments", "Segments per Generated Muons ; Segments per Gen; Entries", 6, 0, 6);
        m_plots["hGenTP"] = new TH1D("hGenTP", "Trigger Primitives per Generated Muons ; Trigger Primitives per Gen; Entries", 6, 0, 6);

        m_plots2["hGenIdxVsNSeg"] = new TH2D("hGenIdxVsNSeg", "GenMuon Index vs Number of Segments; GenMuon Index; Number of Segments", 3750, 0, 3750, 100, 0, 6);
        // m_plots2["hGenIdxVsNSeg"] = new TH2D("hGenIdxVsNSeg", "GenMuon Index vs Number of Segments; GenMuon Index; Number of Segments", 80, 0, 80, 100, 0, 6);
        
        m_plots["hGenEta"] = new TH1D("hGenEta", "Gen Muon #eta distribution ; #eta; Entries", 200, -1.5, +1.5);
        m_plots["hGenPt"] = new TH1D("hGenPt", "Gen Muon pT distribution ; #eta; Entries", 200, 0, 200);
        // m_plots["hGenEta"] = new TH1D("hGenEta", "Gen Muon #eta distribution ; #eta; Entries", 200, -1.5, +1.5);

        m_plots2["hGenEtaVsSegEta"] = new TH2D("hGenEtaVsSegEta", "Eta Gen vs Eta Segments; Eta Gen; Eta Segments", 100, -4, 4, 100, -4, 4);
        m_plots2["hGenPhiVsSegPhi"] = new TH2D("hGenPhiVsSegPhi", "Phi Gen vs Phi Segments; Phi Gen; Phi Segments", 100, -4, 4, 100, -4, 4);

        m_plots["EffEtaGenRec_total"] = new TH1D("EffEtaGenRec_total", "Muon Reconstruction Efficiency; #eta; Efficiency", 100, -2, 2);
        m_plots["EffEtaGenRec_matched"] = new TH1D("EffEtaGenRec_matched", "Muon Reconstruction Efficiency; #eta; Efficiency", 100, -2, 2);



        m_plots["hSegmentPsi"] = new TH1D("hSegmentPsi", "Segment Psi distribution ; Psi; Entries", 200, -60, +60);
        m_plots2["hSegmentPsiVST0"] = new TH2D("hSegmentPsiVST0", "Segment Psi distribution vs segment t0; Psi; Segment t0 (ns)", 200, -50, +50, 200, -100, 100);
        m_plots["hGenSegDeltaPhi"] = new TH1D("hGenSegDeltaPhi", "Gen Muon - Segment Delta Phi distribution ; Delta Phi; Entries", 600, 0, 0.5);
        m_plots["hGenSegDeltaEta"] = new TH1D("hGenSegDeltaEta", "Gen Muon - Segment Delta Eta distribution ; Delta Eta; Entries", 600, 0, 0.5);
        for (const auto & chamb : chambTag) {
            for (const auto & wheel : wheelTag) {
                m_plots["hGenSegDeltaPhi"+wheel+chamb] = new TH1D(("hGenSegDeltaPhi"+wheel+chamb).c_str(),
                "Gen Muon - Segment Delta Phi distribution ; Delta Phi; Entries", 600, 0, 0.5);
                m_plots["hGenSegDeltaEta"+wheel+chamb] = new TH1D(("hGenSegDeltaEta"+wheel+chamb).c_str(),
                "Gen Muon - Segment Delta Eta distribution ; Delta Eta; Entries", 600, 0,  0.5);

                m_plots["hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched"] = new TH1D( ("hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched").c_str(),
                ("hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched; Time of the TPs associated with prompt muons [ns]; Entries").c_str(), 27, -10, 10); // 40, 0, 700  // 40, 630, 650

                m_plots["hPh2TpgPhiEmuAmBX"+wheel+chamb+"_matched"] = new TH1D( ("hPh2TpgPhiEmuAmBX"+wheel+chamb+"_matched").c_str(),
                ("hPh2TpgPhiEmuAmBX"+wheel+chamb+"_matched; BXs of the TPs associated with prompt muons [ns]; Entries").c_str(), 20, 10, 30); // 40, 0, 700  // 40, 630, 650
            }
        }

        for (const auto & algo : algoTag)
        {
            m_plots2["hSegmentPsiVSDeltaT0" + algo] = new TH2D(("hSegmentPsiVSDeltaT0_" + algo).c_str(),
            "Segment Psi distribution vs Delta t0; Psi; Delta t0 (ns)",
            200, -50, +50, 100, -50, 50);
            m_plots["hPrimPsi" + algo] = new TH1D(("hPrimPsi_" + algo).c_str(),
            (algo + " Primitives Psi distribution ; Psi; Entries").c_str(),
            200, -60, +60);
            m_plots2["hBXvsPrimPsi" + algo] = new TH2D(("hBXvsPrimPsi_" + algo).c_str(),
            (algo + " BX vs Primitives Psi distribution ; BX; Psi").c_str(),
            11, -5.5, 5.5, 13 ,-65., 65.);
            m_plots["hDeltaPhi" + algo] = new TH1D(("hDeltaPhi_" + algo).c_str(),
            (algo + " Primitive - Segment Delta Phi distribution ; Delta Phi; Entries").c_str(),
            600, 0, 0.1);
            m_plots["hEffvsSlope" + algo + "matched"] = new TH1D(("hEff_" + algo + "_matched" ).c_str(),
            ("Efficiency for " + algo + "; Local Direction; Efficiency").c_str(),
            50, -50, 50);
            m_plots["hEffvsSlope" + algo + "total"] = new TH1D(("hEff_" + algo + "_total" ).c_str(),
            ("Efficiency for "  + algo + "; Local Direction; Efficiency").c_str(),
            50, -50, 50);
            m_plots["hEffvsLxy" + algo + "matched"] = new TH1D(("hEffLxy_" + algo + "_matched" ).c_str(),
            ("Efficiency for " + algo + "; Gen muon Lxy; Efficiency").c_str(),
            50, 0, 310);
            m_plots["hEffvsLxy" + algo + "total"] = new TH1D(("hEffLxy_" + algo + "_total" ).c_str(),
            ("Efficiency for "  + algo + "; Gen muon Lxy; Efficiency").c_str(),
            50, 0, 310);
            for (const auto & chamb : chambTag)
            {
                for (const auto & total : totalTag)
                {
                    m_plots["Eff_" + chamb + "_" + algo + "_" + total] = new TH1D(("hEff_" + chamb + "_" + algo + "_" + total).c_str(),
                    ("Efficiency for " + chamb + " " + algo + "; Sector; Efficiency").c_str(),
                    5, -2.5, +2.5);
                    m_plots["SegEff_" + chamb + "_" + algo + "_" + total] = new TH1D(("hSegEff_" + chamb + "_" + algo + "_" + total).c_str(),
                    ("Segment efficiency for " + chamb + "; Sector; Efficiency").c_str(),
                    5, -2.5, +2.5);
                    m_plots["EffNoBX_" + chamb + "_" + algo + "_" + total] = new TH1D(("hEffNoBX_" + chamb + "_" + algo + "_" + total).c_str(),
                    ("Efficiency for " + chamb + " " + algo + "; Sector; Efficiency").c_str(),
                    5, -2.5, +2.5);
                    m_plots["EffEta_" + chamb + "_" + algo + "_" + total] = new TH1D(("hEffEta_" + chamb + "_" + algo + "_" + total).c_str(),
                    ("Efficiency vs Eta for " + chamb + " " + algo + "; #eta; Efficiency").c_str(),
                    100, -1.5, +1.5);
                    for (const auto & wheel : wheelTag)
                    {
                    m_plots["hEffvsSlope" + algo + chamb + wheel + total] = new TH1D(("hEff_" + wheel + "_" + chamb + "_" + algo + "_" + total ).c_str(),
                        ("Efficiency for " + wheel + " " + chamb + " " + algo + "; Local Direction; Efficiency").c_str(),
                    50, -50, 50);
                    m_plots["hEffvsLxy" + algo + chamb + wheel + total] = new TH1D(("hEffLxy_" + wheel + "_" + chamb + "_" + algo + "_" + total ).c_str(),
                        ("Efficiency for " + wheel + " " + chamb + " " + algo + "; Gen muon Lxy; Efficiency").c_str(),
                    50, 0, 310);
                    }
                }
            }
        }

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

        std::vector<std::string> chambTags = { "MB1", "MB2", "MB3", "MB4"};
        std::vector<std::string> whTags    = { "Wh.-2", "Wh.-1", "Wh.0", "Wh.+1", "Wh.+2"};
        std::vector<std::string> secTags   = { "Sec1", "Sec2", "Sec3", "Sec4", "Sec5", "Sec6", "Sec7", "Sec8","Sec9","Sec10","Sec11","Sec12","Sec13","Sec14"};

        

        // ------------------------------------------------------------------------------
        // Loop in the events
        // ------------------------------------------------------------------------------
        // nEntries = 100;   // 100   nEntries
        if (testFlag){
            nEntries = 10;
            std::cout << "FOR TESTE:" <<std::endl;
        }
        std::cout << "Total entries:" << nEntries <<std::endl;

        int idxGen = 0;
        for (Long64_t iEvent = 0; iEvent < nEntries; ++iEvent) { 

            tree->GetEntry(iEvent);
            branch_gen_nGenParts->GetEntry(iEvent);
            branch_ph2TpgPhiEmuAm_nTrigs->GetEntry(iEvent);



            m_plots["hNTrigs"] -> Fill( ph2TpgPhiEmuAm_nTrigs );

            numTPEvent = 0;
            denTPEvent = 0;
            // -----------------------------
            // loop Gen Particle
            // -----------------------------
            for (int iGenPart = 0; iGenPart < gen_nGenParts; ++iGenPart) {
                int numTP = 0;
                int denTP = 0;
                int NbestSegment = 0;
                int Ntrigger = 0;
                
                std::cout << "==============================================================================" << std::endl;
                std::cout << "iEvent " << iEvent << ", iGenPart " << iGenPart <<  " | gen_nGenParts: " << gen_nGenParts << " | " << "gen pt: "<< gen_pt->at(iGenPart) << " | " << "gen eta: "<< gen_eta->at(iGenPart) << " | gen phi: "<< gen_phi->at(iGenPart) << std::endl;
                std::cout << "==============================================================================" << std::endl;

                m_plots["hGenEta"] -> Fill( gen_eta->at(iGenPart) );
                m_plots["EffEtaGenRec_total"] -> Fill( gen_eta->at(iGenPart) );

                if (std::abs(gen_pdgId->at(iGenPart)) != 13 || gen_pt->at(iGenPart) < m_minMuPt) continue;



                std::vector<std::size_t> bestSegIndex = { 999, 999, 999, 999 };
                std::vector<Int_t> bestSegNHits       = { 0, 0, 0, 0 };
                    
                // -----------------------------
                // Loop in the Segments (Reco Muons)
                // -----------------------------
                bool genFill = false;
                std::cout << "Loop in the Segments and Gen Particle Matching " << std::endl;
                std::cout << "Number of ph2 Segments in this event: " << ph2Seg_nSegments << std::endl;
                for (std::size_t iSeg = 0; iSeg < ph2Seg_nSegments; ++iSeg) {

                    Int_t segSt    = ph2Seg_station->at(iSeg);
                    Int_t segNHits = ph2Seg_phi_nHits->at(iSeg);
                    Int_t segZNHits = ph2Seg_z_nHits->at(iSeg);
                    
                    // -------------------------------------
                    // Segments quality selection
                    // -------------------------------------
                    if (abs(ph2Seg_phi_t0->at(iSeg)) > m_maxSegT0 ) continue;
                    // if (abs(seg_wheel->at(iSeg))==2 && segSt==4) cout << "Found! muSegDPhi=" << muSegDPhi<< " genPhi="<< gen_phi->at(iGenPart) << " seg_posGlb_phi=" << seg_posGlb_phi->at(iSeg)  << " muSegDEta=" << muSegDEta << " segNHits=" << segNHits << " segZNHits=" << segZNHits  << endl;
                    
                    Double_t muSegDPhi = std::abs(acos(cos(gen_phi->at(iGenPart) - ph2Seg_posGlb_phi->at(iSeg))));
                    Double_t muSegDEta = std::abs(gen_eta->at(iGenPart) - ph2Seg_posGlb_eta->at(iSeg));
                
                    if (muSegDPhi < m_maxMuSegDPhi &&
                        muSegDEta < m_maxMuSegDEta &&
                        segNHits >= m_minSegHits &&
                        (segZNHits >= m_minZSegHits  || segSt==4) &&
                        segNHits >= bestSegNHits.at(segSt - 1))
                    {
                        // Update Best Segment. Stores the hit count and index of the best-matched segment per station.
                        bestSegNHits[segSt - 1] = segNHits; 
                        bestSegIndex[segSt - 1] = iSeg;
                        //   if (abs(seg_wheel->at(iSeg))==2 && segSt==4) cout << "Found!" << endl;
                    }

                    if (genFill == false) {
                        m_plots["EffEtaGenRec_matched"] -> Fill( gen_eta->at(iGenPart) );
                        genFill = true;
                    }

                }// END loop segments

                // Print elements of the vector for test
                std::cout << " \n ------------------------------------------- \n";
                std::cout << "Best Segments Index" << std::endl;
                for (size_t iSeg = 0; iSeg < bestSegIndex.size(); ++iSeg) {
                    std::cout << bestSegIndex[iSeg] << " , ";
                }
                std::cout << " \n ------------------------------------------- \n";
                for (size_t iSeg = 0; iSeg < bestSegIndex.size(); ++iSeg) {
                    if (bestSegIndex[iSeg] == 999) continue;
                    Int_t segSt     = ph2Seg_station->at(bestSegIndex[iSeg]);
                    Int_t segWh  = ph2Seg_wheel->at(bestSegIndex[iSeg]);
                    Int_t segSec = ph2Seg_sector->at(bestSegIndex[iSeg]);
                    if (segSec == 13) segSec = 4;
                    if (segSec == 14) segSec = 10;
                    std::cout << "  Seg Wheel: " << segWh << " | Seg Sector: "<< segSec << " | Seg Station: " << segSt <<  std::endl;
                }
                std::cout << "Best Segments Number of Hits" << std::endl;
                for (size_t iSeg = 0; iSeg < bestSegNHits.size(); ++iSeg) {
                    std::cout << bestSegNHits[iSeg] << " , ";
                }
                std::cout << " \n";

                // Quality Code
                // LOWQ 1 -> 3 hits
                // CLOWQ 2 -> 3+2
                // HIGHQ 3 -> 4 hits
                // CHIGHQ 4 -> 4+2
                // LOWLOWQ 6 -> 3+3
                // HIGHLOWQ 7 -> 4+3
                // HIGHHIGHQ 8 -> 4+4

                TString quality_;
                quality_ = "All";
                
                // quality_ = "Q8";

                // enum MP_QUALITY { NOPATH = 0, LOWQ = 1, CLOWQ = 2, HIGHQ = 3, CHIGHQ = 4, LOWLOWQ = 6, HIGHLOWQ = 7, HIGHHIGHQ = 8 };
                int LOWQ = 1;
                int CLOWQ = 2;
                int HIGHQ = 3;
                int CHIGHQ = 4;
                int LOWLOWQ = 6;
                int HIGHLOWQ = 7;
                int HIGHHIGHQ = 8;
                
                int minQuality = -99;
                int minQualityPh1 = -99;
                int maxIndex = 9999;
                bool qualityMatched = false;
                bool qualityORSegs = false;
                bool qualityORSegsClus = false;
                bool qualityMatchedORSegs = false;
                bool qualityMatchedORSegsClus = false;
                bool qualityCorrelated = false;
                bool qualityConfirmed = false;
                bool qualityLegacy = false;
                
                if (quality_ == "nothreehits"){
                minQuality = CLOWQ;
                }
                else if (quality_ == "index0")
                maxIndex = 0;
                else if (quality_ == "index01")
                maxIndex = 1;
                else if (quality_ == "index012")
                maxIndex = 2;
                else if (quality_ == "index0123")
                maxIndex = 3;
                else if (quality_ == "withmatchedthreehits")
                qualityMatched = true;
                else if (quality_ == "qualityORSegs")
                qualityORSegs = true;
                else if (quality_ == "qualityORSegsClus")
                qualityORSegsClus = true;
                else if (quality_ == "qualityMatchedORSegs")
                qualityMatchedORSegs = true;
                else if (quality_ == "qualityMatchedORSegsClus")
                qualityMatchedORSegsClus = true;
                else if (quality_ == "correlated")
                qualityCorrelated = true;
                else if (quality_ == "confirmed")
                qualityConfirmed = true;
                else if (quality_ == "legacy")
                qualityLegacy = true;
                else if (quality_ == "Q8" ){
                minQuality = HIGHHIGHQ;
                minQualityPh1 = 6;
                }
                else if (quality_ == "All" )
                minQuality = -999;
                else {
                cout << "Error: Efficiency category not found" << endl;
                //  std::exit(EXIT_FAILURE);
                }

                // --------------------------
                // Loop best segments
                // --------------------------
                std::cout << "  Loop best segments " << std::endl; 
                for (const auto & iSeg : bestSegIndex)
                {
                    std::cout << "  --------------" << std::endl;
                    std::cout << "  Segment Index " << iSeg << std::endl; 
                    if (iSeg == 999) continue;

                    NbestSegment++;

                    Int_t segSt    = ph2Seg_station->at(iSeg);
                    Int_t segNHits = ph2Seg_phi_nHits->at(iSeg);
                    Int_t segZNHits = ph2Seg_z_nHits->at(iSeg);

                    Double_t muSegDPhi = std::abs(acos(cos(gen_phi->at(iGenPart) - ph2Seg_posGlb_phi->at(iSeg))));
                    Double_t muSegDEta = std::abs(gen_eta->at(iGenPart) - ph2Seg_posGlb_eta->at(iSeg));

                    m_plots["hSegmentPsi"] -> Fill( atan ( (ph2Seg_dirLoc_x->at(iSeg) / ph2Seg_dirLoc_z->at(iSeg)) ) * 360 / (2*TMath::Pi())  );
                    m_plots2["hSegmentPsiVST0"] -> Fill( atan ( (ph2Seg_dirLoc_x->at(iSeg) / ph2Seg_dirLoc_z->at(iSeg)) ) * 360 / (2*TMath::Pi()) , ph2Seg_phi_t0->at(iSeg) );
                    m_plots["hGenSegDeltaPhi"] -> Fill( muSegDPhi );
                    m_plots["hGenSegDeltaPhi"+whTags.at(ph2Seg_wheel->at(iSeg)+2)+chambTags.at(segSt-1)] -> Fill( muSegDPhi );
                    m_plots["hGenSegDeltaEta"] -> Fill( muSegDEta );
                    m_plots["hGenSegDeltaEta"+whTags.at(ph2Seg_wheel->at(iSeg)+2)+chambTags.at(segSt-1)] -> Fill( muSegDEta );

                    m_plots2["hGenEtaVsSegEta"] -> Fill( gen_eta->at(iGenPart), ph2Seg_posGlb_eta->at(iSeg) );
                    m_plots2["hGenPhiVsSegPhi"] -> Fill( gen_phi->at(iGenPart) , ph2Seg_posGlb_phi->at(iSeg) );



                    Int_t segWh  = ph2Seg_wheel->at(iSeg);
                    Int_t segSec = ph2Seg_sector->at(iSeg);
                    if (segSec == 13) segSec = 4;
                    if (segSec == 14) segSec = 10;


                    std::string chambTag = chambTags.at(segSt - 1);
                    std::string whTag    = whTags.at(segWh + 2);
                    std::string secTag   = secTags.at(segSec - 1);

                    std::cout << "  Seg Wheel: " << segWh << " | Seg Sector: "<< segSec << " | Seg Station: " << segSt <<  std::endl;

                    if (ph2Seg_phi_t0->at(iSeg) > -500)
                    {
                        m_plots["Eff_" + chambTag + "_Ph1_total"]->Fill(segWh);
                        m_plots["EffNoBX_" + chambTag + "_Ph1_total"]->Fill(segWh);
                        m_plots["EffEta_" + chambTag + "_Ph1_total"]->Fill(gen_eta->at(iGenPart));
                        m_plots["hEffvsSlopePh1" + chambTag + whTag + "total"] -> Fill(atan ( (ph2Seg_dirLoc_x->at(iSeg) / ph2Seg_dirLoc_z->at(iSeg)) ) * 360 / (2*TMath::Pi()) );
                        m_plots["hEffvsSlopePh1total"] -> Fill(atan ( (ph2Seg_dirLoc_x->at(iSeg) / ph2Seg_dirLoc_z->at(iSeg)) ) * 360 / (2*TMath::Pi()) );
                        // if (DM_) m_plots["hEffvsLxyPh1" + chambTag + whTag + "total"] -> Fill( gen_lxy->at(iGenPart) );
                        // if (DM_) m_plots["hEffvsLxyPh1total"] -> Fill( gen_lxy->at(iGenPart) );
                    }

                    // ==================== VARIABLES FOR THE ANALYTICAL METHOD ALGORITHM
                    // Int_t    bestTPAM = -1;
                    Int_t    bestTPAM = -999; // For test
                    Int_t    bestTPNoBXAM = -1;
                    Int_t    AMRPCflag= -1;
                    Double_t bestSegTrigAMDPhi = 1000;
                    Double_t bestSegTrigAMDPhiNoBX = 1000;
                    Double_t bestAMDPhi = 0;
                    Int_t    besttrigAMBX = 0;

                    Double_t trigAMt0 = -999;

                    // -----------------------------
                    // Loop in the AM TP
                    // -----------------------------
                    std::cout << "      Loop in the AM TP " << std::endl;
                    std::cout << "      Total number of TP in this event: "<< ph2TpgPhiEmuAm_nTrigs << std::endl;  
                    for (std::size_t iTrigAM = 0; iTrigAM < ph2TpgPhiEmuAm_nTrigs; ++iTrigAM){

                        // if 
                        // std::cout << "      Loop in the AM TP " << std::endl;

                        Int_t trigAMWh  = ph2TpgPhiEmuAm_wheel->at(iTrigAM);
                        Int_t trigAMSec = ph2TpgPhiEmuAm_sector->at(iTrigAM);
                        Int_t trigAMSt  = ph2TpgPhiEmuAm_station->at(iTrigAM);
                        Int_t trigAMBX  = ph2TpgPhiEmuAm_BX->at(iTrigAM);
                        Int_t trigAMqual = ph2TpgPhiEmuAm_quality->at(iTrigAM);
                        Int_t trigAMrpc  = ph2TpgPhiEmuAm_rpcFlag->at(iTrigAM);

                        // m_plots["hPh2TpgPhiEmuAmBX"+whTag+chambTag+"_matched"]->Fill(trigAMBX);

                        // -----------------------------
                        // SEGMENTS AND TP MATCHING
                        // -----------------------------
                        if (segWh == trigAMWh && segSec == trigAMSec && segSt  == trigAMSt) {
                            
                            Double_t trigGlbPhi    = trigPhiInRad(ph2TpgPhiEmuAm_phi->at(iTrigAM),trigAMSec);
                            Double_t finalAMDPhi   = ph2Seg_posGlb_phi->at(iSeg) - trigGlbPhi;
                            Double_t segTrigAMDPhi = abs(acos(cos(finalAMDPhi)));
                            std::cout << "      iTrigAM: " << iTrigAM << " | Wheel: "<< trigAMWh << " | Sector: " << trigAMSec << " | Station: " << trigAMSt << " | trigAMBX: " << trigAMBX << " | segTrigAMDPhi: " << segTrigAMDPhi <<  std::endl;
                            std::cout << "          trigGlbPhi: " << trigGlbPhi << " | finalAMDPhi: " << finalAMDPhi << " | segTrigAMDPhi: " << segTrigAMDPhi <<  std::endl;

                            m_plots["hPrimPsiAM"] -> Fill( ph2TpgPhiEmuAm_dirLoc_phi->at(iTrigAM) );
                            m_plots["hDeltaPhiAM"] -> Fill( segTrigAMDPhi );
                            m_plots2["hBXvsPrimPsiAM"] -> Fill ( trigAMBX - 20 , atan ( (ph2Seg_dirLoc_x->at(iSeg) / ph2Seg_dirLoc_z->at(iSeg)) ) * 360 / (2*TMath::Pi()));
                            if (segNHits == 8) 
                                m_plots["SegEff_" + chambTag + "_AM_matched"] -> Fill(segWh);
                            m_plots["SegEff_" + chambTag + "_AM_total"] -> Fill(segWh);
                            m_plots2["hSegmentPsiVSDeltaT0AM"]->Fill(  atan ( (ph2Seg_dirLoc_x->at(iSeg) / ph2Seg_dirLoc_z->at(iSeg)) ) * 360 / (2*TMath::Pi()) , ph2TpgPhiEmuAm_t0->at(iTrigAM) - 20*25 - ph2Seg_phi_t0->at(iSeg) );

                            if (ph2TpgPhiEmuAm_index->at(iTrigAM) > maxIndex ) continue;
                            // if (ph2TpgPhiEmuAm_quality->at(iTrigAM) < minQuality ) continue;
                            if (qualityORSegs && ( (trigAMqual < LOWQ && trigAMqual > -1) || ( trigAMqual ==-1 && trigAMrpc!=2 ) )) continue;
                            if (qualityORSegsClus &&  (trigAMqual < LOWQ && trigAMqual > -1)  ) continue;
                            if (qualityMatched && ( (ph2TpgPhiEmuAm_quality->at(iTrigAM) < LOWQ && ph2TpgPhiEmuAm_rpcFlag->at(iTrigAM)==0 ) || ( ph2TpgPhiEmuAm_quality->at(iTrigAM) ==-1 ) ) ) continue;
                            if (qualityMatchedORSegs && ( ( (trigAMqual < LOWQ && trigAMrpc==0 ) && trigAMqual > -1) || ( trigAMqual ==-1 && trigAMrpc!=2 ) )) continue;
                            if (qualityMatchedORSegsClus && ( ( (trigAMqual < LOWQ && trigAMrpc==0 ) && trigAMqual > -1) )) continue;
                            if (qualityCorrelated && (trigAMqual < LOWLOWQ)) continue;
                            if (qualityConfirmed && (trigAMqual < LOWLOWQ && trigAMqual != CLOWQ && trigAMqual != CHIGHQ)) continue;
                            if (qualityLegacy && (trigAMqual < HIGHQ)) continue;

                            // std::cout << "   Denominator -------- \n " << std::endl; 

                            if ((segTrigAMDPhi < m_maxSegTrigDPhi) && (trigAMBX == 20) && (bestSegTrigAMDPhi > segTrigAMDPhi) && (ph2TpgPhiEmuAm_quality->at(iTrigAM) >= minQuality))
                            // if ( trigAMBX == 20 ) // For test
                            {
                                bestTPAM          = iTrigAM;
                                besttrigAMBX      = trigAMBX;
                                bestSegTrigAMDPhi = segTrigAMDPhi;
                                // bestAMDPhi        = TVector2::Phi_mpi_pi(finalAMDPhi);
                                AMRPCflag         = ph2TpgPhiEmuAm_rpcFlag->at(iTrigAM);

                                // std::cout << "   bestTPAM : " << bestTPAM << std::endl; 
                            }
                            if (segTrigAMDPhi < m_maxSegTrigDPhi && (bestSegTrigAMDPhiNoBX > segTrigAMDPhi) && (ph2TpgPhiEmuAm_quality->at(iTrigAM) >= minQuality))
                            {
                                bestTPNoBXAM          = iTrigAM;
                                bestSegTrigAMDPhiNoBX = segTrigAMDPhi;
                                trigAMt0 = ph2TpgPhiEmuAm_t0->at(iTrigAM);

                            }

                            // For test. This is to apply the 0.1 cut in the denominator as well
                            // if ((segTrigAMDPhi < m_maxSegTrigDPhi) && (bestSegTrigAMDPhi > segTrigAMDPhi) && (ph2TpgPhiEmuAm_quality->at(iTrigAM) >= minQuality)){

                            //     bestTPAM = -1;

                            // }

                        } // End Conditional Matching

                    } // End Loop TP        

                    // ----------------------------
                    // NUMERATOR
                    // ----------------------------
                    if (bestTPAM > -1 && ph2Seg_phi_t0->at(iSeg) > -500)
                    {
                        std::cout << "  Fill MATCHING Histograms (Efficient)" << std::endl;
                        std::cout << "  bestTPAM: "<< bestTPAM << std::endl;

                        Ntrigger++;

                        // cout << iEvent << " " << 1 << " "<< segWh << " " << segSec << " " << segSt << " " << ph2Seg_phi_nHits->at(iSeg) << " " << getPh1Hits(segWh,segSec,segSt) << " " << getPh2Hits(segWh,segSec,segSt) <<endl;
                        //        cout << "Efficient event " <<  iEvent << " in " << whTag << " " << secTag << " " << chambTag << " Segment hits: " << ph2Seg_phi_nHits->at(iSeg) << " Segment Position: " << ph2Seg_posLoc_x->at(iSeg) <<endl;
                        // cout << "Efficient event " <<  iEvent << " in " << whTag << " " << secTag << " " << chambTag << " Segment hits: " << ph2Seg_phi_nHits->at(iSeg) << " Segment Position: " << ph2Seg_posLoc_x->at(iSeg) << " Primitive iTrig " << bestTPAM << " out of " <<  ph2TpgPhiEmuAm_nTrigs  << " Quality: " << ph2TpgPhiEmuAm_quality->at(bestTPAM) << " t0=" << ph2TpgPhiEmuAm_t0->at(bestTPAM)  <<endl;
                        // cout << "Eficiente!" << endl;

                        // cout << iEvent << " " << 1 << " "<< segWh << " " << segSec << " " << segSt << " " << ph2Seg_phi_nHits->at(iSeg) << " " <<endl;
                        // cout << "Efficient event " <<  iEvent << " in " << whTag << " " << secTag << " " << chambTag << " Segment hits: " << ph2Seg_phi_nHits->at(iSeg) << " Segment Position: " << ph2Seg_posLoc_x->at(iSeg) <<endl;
                        // cout << "Efficient event " <<  iEvent << " in " << whTag << " " << secTag << " " << chambTag << " Segment hits: " << ph2Seg_phi_nHits->at(iSeg) << " Segment Position: " << ph2Seg_posLoc_x->at(iSeg) << " Primitive iTrig " << bestTPAM << " out of " <<  ph2TpgPhiEmuAm_nTrigs  << " Quality: " << ph2TpgPhiEmuAm_quality->at(bestTPAM) << " t0=" << ph2TpgPhiEmuAm_t0->at(bestTPAM)  <<endl;
                        // cout << "Eficiente!" << endl;
                        
                        // std::cout << "NUMERATOR Here: " << std::endl;
                        numTP++;
                        numTPEvent++;
                        numTPAll++;

                        m_plots["Eff_" + chambTag + "_AM_matched"]->Fill(segWh);
                        m_plots["EffEta_" + chambTag + "_AM_matched"]->Fill(gen_eta->at(iGenPart));
                        m_plots["hEffvsSlopeAM" + chambTag + whTag + "matched"] -> Fill(atan ( (ph2Seg_dirLoc_x->at(iSeg) / ph2Seg_dirLoc_z->at(iSeg)) ) * 360 / (2*TMath::Pi()) );
                        // if (DM_) m_plots["hEffvsLxyAM" + chambTag + whTag + "matched"] -> Fill( gen_lxy->at(iGenPart) );
                        // if (DM_) m_plots["hEffvsLxyAMmatched"] -> Fill( gen_lxy->at(iGenPart) );
                        m_plots["hEffvsSlopeAMmatched"] -> Fill(atan ( (ph2Seg_dirLoc_x->at(iSeg) / ph2Seg_dirLoc_z->at(iSeg)) ) * 360 / (2*TMath::Pi()) );
                        if (AMRPCflag > 0) m_plots["Eff_" + chambTag + "_AM+RPC_matched"]->Fill(segWh);

                        std::cout << "            trigAMt0: "<< trigAMt0 << std::endl;
                        // trigAMt0 = (trigAMt0 * 25 / 32); // DCS to ns   OBS: Need to change the range in the histogram to [-10,10]
                        trigAMt0 = (trigAMt0 * 25 / 32) -500;
                        std::cout << "            trigAMt0: "<< trigAMt0 << std::endl;
                        m_plots["hPh2TpgPhiEmuAmT0"+whTag+chambTag+"_matched"]->Fill(trigAMt0);

                        m_plots["hPh2TpgPhiEmuAmBX"+whTag+chambTag+"_matched"]->Fill(besttrigAMBX);

                        

                    } else if (bestTPAM  < 0 && ph2Seg_phi_t0->at(iSeg) > -500) {
                        // cout << iEvent << " " << -1 << " "<< segWh << " " << segSec << " " << segSt << " " << ph2Seg_phi_nHits->at(iSeg) << " " << getPh1Hits(segWh,segSec,segSt) << " " << getPh2Hits(segWh,segSec,segSt) <<endl;
                        // cout << "Inefficient event " <<  iEvent << " in " << whTag << " " << secTag << " " << chambTag << " Segment hits: " << ph2Seg_phi_nHits->at(iSeg) << " Segment Position: " << ph2Seg_posLoc_x->at(iSeg) <<endl;
                        // cout << "Inefficient event " <<  iEvent << " in " << whTag << " " << secTag << " " << chambTag << " Segment hits: " << ph2Seg_phi_nHits->at(iSeg) << " Segment Position: " << ph2Seg_posLoc_x->at(iSeg) << " Primitive iTrig " << bestTPAM << " out of " <<  ph2TpgPhiEmuAm_nTrigs  <<endl;

                        // cout << iEvent << " " << -1 << " "<< segWh << " " << segSec << " " << segSt << " " << ph2Seg_phi_nHits->at(iSeg) <<endl;
                        // cout << "Inefficient event " <<  iEvent << " in " << whTag << " " << secTag << " " << chambTag << " Segment hits: " << ph2Seg_phi_nHits->at(iSeg) << " Segment Position: " << ph2Seg_posLoc_x->at(iSeg) <<endl;
                        // cout << "Inefficient event " <<  iEvent << " in " << whTag << " " << secTag << " " << chambTag << " Segment hits: " << ph2Seg_phi_nHits->at(iSeg) << " Segment Position: " << ph2Seg_posLoc_x->at(iSeg) << " Primitive iTrig " << bestTPAM << " out of " <<  ph2TpgPhiEmuAm_nTrigs  <<endl;
                    }
                    if (bestTPNoBXAM > -1 && ph2Seg_phi_t0->at(iSeg) > -500)
                    {
                        m_plots["EffNoBX_" + chambTag + "_AM_matched"]->Fill(segWh);
                    }
                            
                    // ----------------------------
                    // DENOMINATOR
                    // ----------------------------
                    if (ph2Seg_phi_t0->at(iSeg) > -500)
                    // if (  bestTPAM > -500 && ph2Seg_phi_t0->at(iSeg) > -500) // For test. This is to apply the 0.1 cut in the denominator as well
                    {
                        std::cout << "  Fill TOTAL Histograms" << std::endl;

                        m_plots["Eff_" + chambTag + "_AM_total"]->Fill(segWh);
                        m_plots["EffNoBX_" + chambTag + "_AM_total"]->Fill(segWh);
                        m_plots["EffEta_" + chambTag + "_AM_total"]->Fill(gen_eta->at(iGenPart));
                        m_plots["hEffvsSlopeAM" + chambTag + whTag + "total"] -> Fill(atan ( (ph2Seg_dirLoc_x->at(iSeg) / ph2Seg_dirLoc_z->at(iSeg)) ) * 360 / (2*TMath::Pi()) );
                        m_plots["hEffvsSlopeAMtotal"] -> Fill(atan ( (ph2Seg_dirLoc_x->at(iSeg) / ph2Seg_dirLoc_z->at(iSeg)) ) * 360 / (2*TMath::Pi()) );
                        // if (DM_) m_plots["hEffvsLxyAM" + chambTag + whTag + "total"] -> Fill( gen_lxy->at(iGenPart) );
                        // if (DM_) m_plots["hEffvsLxyAMtotal"] -> Fill( gen_lxy->at(iGenPart) );
                        m_plots["Eff_" + chambTag + "_AM+RPC_total"]->Fill(segWh);

                        // std::cout << "DENOMINATOR Here: " << std::endl;
                        denTP++;
                        denTPEvent++;
                        denTPAll++;
                    }

                } // End Loop best segments 

                idxGen++;
                m_plots2["hGenIdxVsNSeg"] -> Fill( idxGen, NbestSegment );

                m_plots["hGenSegments"] -> Fill( NbestSegment );
                m_plots["hGenTP"] -> Fill( Ntrigger );

                // double eff = numTP / denTP;
                std::cout << "**********************" <<  std::endl;
                std::cout << "Numerator per Gen: "<<  numTP << std::endl;
                std::cout << "DENOMINATOR per Gen: "<<  denTP << std::endl;
                // std::cout << "eff per Event: "<<  eff << std::endl;
                std::cout << "**********************" <<  std::endl;
                
            } // END Loop Gen
            

            // std::cout << "**********************" <<  std::endl;
            std::cout << "Numerator Event: "<<  numTPEvent << std::endl;
            std::cout << "DENOMINATOR Event: "<<  denTPEvent << std::endl;
            // std::cout << "**********************" <<  std::endl;   

        } // END Loop Event 

        std::cout << "**********************" <<  std::endl;
        std::cout << "Numerator : "<<  numTPAll << std::endl;
        std::cout << "DENOMINATOR : "<<  denTPAll << std::endl;
        std::cout << "**********************" <<  std::endl; 

        std::string outputDir = "";
        std::string histoDir = "";
        std::string effDir = "";
        if (file_name.find("noRPC") != std::string::npos) 
        {
            std::cout << "Found 'noRPC' in the filename!" << std::endl;
            outputDir = "output/noRPC/";
            histoDir =  "output/noRPC/histograms/";
            effDir =    "output/noRPC/histograms/effPlots/";
        } 
        else {
            std::cout << "'noRPC' not found." << std::endl;
            outputDir = "output/RPC/";
            histoDir =  "output/RPC/histograms/";
            effDir =    "output/RPC/histograms/effPlots/";
        }

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
            return;
        }

        // -------------------------------------------
        // Loop over the map to save each histogram in the root file and as png
        // -------------------------------------------
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
            canvas.SaveAs((histoDir + name + ".png").c_str());
        }

        // Manually changing some plots
        // m_plots2["hGenIdxVsNSeg"]->SetStats(0); // Disable statistics box
        // m_plots2["hGenIdxVsNSeg"]->SetMarkerStyle(20);   // 20 = small dots
        // m_plots2["hGenIdxVsNSeg"]->SetMarkerColor(kBlack); // kBlack = ROOT's black color
        // m_plots2["hGenIdxVsNSeg"]->SetMarkerSize(0.5);   // Adjust dot size (optional)
        // m_plots2["hGenIdxVsNSeg"]->Draw("P");  // "P" option draws only points

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
            canvas.SaveAs((histoDir + name + ".png").c_str());
        }
        // Close the file (optional, as it will be automatically closed when outFile goes out of scope)
        outFile.Close();
        std::cout << "All histograms saved in ROOT file: " << outputFile << std::endl;
        std::cout << "All plots saved in: " << outputDir << std::endl;
    }

    std::cout << "----------------------------------" << std::endl;
    std::cout << "TEST FLAG: " << testFlag << std::endl;
    std::cout << "----------------------------------" << std::endl;

} // END Program