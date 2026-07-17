#include <iostream>
#include <string>
#include <typeinfo> // see the type of a variable
#include <fstream> // create and write file
#include <vector>
#include <filesystem>
#include <cmath>
#include <unordered_map>
#include <set>
#include <iomanip> // For std::setprecision
#include <sys/stat.h>
#include <initializer_list>

#include <TFile.h>
#include <TDirectoryFile.h>
#include <TKey.h>
#include <TH1.h>
#include <TH1F.h>
#include <TH2F.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TLegend.h>
#include <TText.h>
#include <TLatex.h>
#include <TObjArray.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TTree.h>
#include <TEfficiency.h>
#include "TMath.h" 
#include <TSystem.h> // For gSystem->mkdir()
#include <TLine.h>

#include <TGraphAsymmErrors.h>
#include <TFrame.h>
#include <TGaxis.h>
#include <TF1.h>


constexpr int TIME_TO_TDC_COUNTS = 32;
constexpr int LHC_CLK_FREQ = 25; // In nanoseconds


constexpr float PHIBRES_CONV = 4096. / 2.;   // 13 bits, [-2, 2]
double phi_DT_MP_conv(double rpc_global_phi, int rpcSector) {
  // Adaptation of https://github.com/cms-sw/cmssw/blob/master/L1Trigger/L1TTwinMux/src/RPCtoDTTranslator.cc#L349

  if (rpcSector == 1)
    return rpc_global_phi;
  else {
    float conversion = 1 / 6.;
    if (rpc_global_phi >= 0)
      return rpc_global_phi - (rpcSector - 1) * M_PI * conversion;
    else
      return rpc_global_phi + (13 - rpcSector) * M_PI * conversion;
  }
}


class BarrelGeo {  // The class
  private:  // Access specifier
    std::vector<std::vector<double>> barrel_geometry; // Attribute

  public:
    BarrelGeo() { }// Constructor
    
    BarrelGeo(const std::string& filename) { // Constructor
        // cout << "Testing!!!!";
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file " << filename << std::endl;
            // return chambers;  // Return empty vector
        }

        std::string line;
        int line_number = 0;
        
        while (std::getline(file, line)) {
            line_number++;
            
            // Skip header lines (lines 1-3)
            if (line_number <= 3) {
                continue;
            }
            // Skip empty lines
            if (line.empty()) {
                continue;
            }
            
            // Parse the data line
            std::istringstream iss(line);
            int station, layer, sector, ring;
            double eta_min, eta_max, phi_min, phi_max;
            
            if (iss >> station >> layer >> sector >> ring 
                    >> eta_min >> eta_max >> phi_min >> phi_max) {
                
                // std::cout << station << " " << layer << " " << sector << " " 
                //             << ring << " " << eta_min << " " << eta_max << " " 
                //             <<phi_min << " " << phi_max << std::endl;

                std::vector<double> tempVec; // tempVec = [station] [layer] [ring] [eta_min] [eta_max] [phi_min] [phi_max] 
                tempVec.push_back(station);
                tempVec.push_back(layer);
                tempVec.push_back(sector);
                tempVec.push_back(ring);
                tempVec.push_back(eta_min);
                tempVec.push_back(eta_max);
                tempVec.push_back(phi_min);
                tempVec.push_back(phi_max);
                barrel_geometry.push_back(tempVec); 
            } else {
                std::cerr << "Warning: Could not parse line " << line_number << ": " << line << std::endl;
            }
        } // End loop file lines
    }

    std::vector<std::vector<double>> StaLaySecRing(double genEta, double genPhi){

        std::vector<std::vector<double>> geo_info;

        // 0=[station] 1=[layer] 2=[sector] 3=[ring] 4=[eta_min] 5=[eta_max] 6=[phi_min] 7=[phi_max]
        for (size_t iGeo = 0; iGeo < barrel_geometry.size(); ++iGeo) {
            
            double geoEtaMin = barrel_geometry[iGeo][4];
            double geoEtaMax = barrel_geometry[iGeo][5];
            double geoPhiMin = barrel_geometry[iGeo][6];
            double geoPhiMax = barrel_geometry[iGeo][7];

            if ( genEta < geoEtaMin) continue;
            if ( genEta > geoEtaMax) continue;
            if ( genPhi < geoPhiMin) continue;
            if ( genPhi > geoPhiMax) continue;
            int geoStation = barrel_geometry[iGeo][0];
            int geoLayer   = barrel_geometry[iGeo][1];
            int geoSector  = barrel_geometry[iGeo][2];
            int geoRing    = barrel_geometry[iGeo][3];
            // std::cout << "Ring:" << geoRing << ", Sector: " << geoSector << ", Station: " << geoStation << ", Leyer: " << geoLayer << std::endl;
            
            std::vector<double> tempVec; // tempVec = [station] [layer] [ring]
            tempVec.push_back(geoStation);
            tempVec.push_back(geoLayer);
            tempVec.push_back(geoSector);
            tempVec.push_back(geoRing);
            geo_info.push_back(tempVec);

        }

        return geo_info;
    }

}; // End Class


bool fileExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

// Organize Wheels and stations in 20 bins for Efficiency plots
int WheelStationToBins (int station, int wheel ){
    int wheelIdx = 0;
    if (station >= 1 && station <= 4 && wheel >= -2 && wheel <= 2) {
        wheelIdx = (station - 1) * 5 + (wheel + 2) + 1;
    }
    return wheelIdx;
}

// bool checkFilesInDirectory(const std::vector<std::string>& filenames, 
//                            const std::string& directory) {
//     bool allExist = true;
    
//     for (const auto& filename : filenames) {
//         std::string fullPath = directory + filename;
        
//         if (fileExists(fullPath)) {
//             std::cout << "✓ Found: " << fullPath << std::endl;
//         } else {
//             std::cout << "✗ Missing: " << fullPath << std::endl;
//             allExist = false;
//         }
//     }
    
//     return allExist;
// }

bool checkFilesInDirectory(const std::string& filename, 
                           const std::string& directory) {
    bool allExist = true;
    std::string fullPath = directory + filename;
    if (fileExists(fullPath)) {
        std::cout << "✓ Found: " << fullPath << std::endl;
    } else {
        std::cout << "✗ Missing: " << fullPath << std::endl;
        allExist = false;
    }
    return allExist;
}

double get_entries(  TH1F *hist) {

   double totalEntries = 0.;

    if (!hist) {
        std::cerr << "Error: Could not retrieve histogram for get_entries() !!!!!" << std::endl;
        return totalEntries = 0.;
    }
    // Get the standard deviation of each histogram
    totalEntries = hist->GetEntries();

    return totalEntries;
}

Double_t trigPhiInRad(Double_t trigPhi, Int_t sector)
{
  double PHIRES_CONV = 65536/0.5; 
  return trigPhi / PHIRES_CONV + TMath::Pi() / 6 * (sector - 1);
}

// Double_t trigPhiInRad(Double_t trigPhi, Int_t sector)
// {
//   return trigPhi / 65536. * 0.8 + TMath::Pi() / 6 * (sector - 1);
// }

// int getPh1Hits(int wh, int se, int st)
// {
//   int sum = 0;
//   for (unsigned int i = 0; i < digi_nDigis; i++){
//     if ( digi_wheel->at(i) == wh &&
//       digi_sector->at(i) == se &&
//     digi_station->at(i) == st ) sum++;
//   }
//   return sum;
// }


void plot_eff(  std::string hName,
                TH1F *hMatched, 
                TH1F *hTotal,
                std::string saveDir ) 
{
    // Check if histograms exist
    if (!hMatched || !hTotal) {
        std::cerr << "Error: Required histograms " << hName  << " not found!" << std::endl;
        return;
    }

    // Create the efficiency plot
    TEfficiency* effPlot = new TEfficiency(*hMatched, *hTotal);
    effPlot->SetName( hName.c_str() );  // Convert to const char*
    // effPlot->SetTitle( (hName+"; Sector ; Efficiency").c_str());
    
    // Style the efficiency plot
    effPlot->SetLineColor(kBlue);
    effPlot->SetMarkerColor(kBlue);
    effPlot->SetMarkerStyle(20);

    // effPlot->GetYaxis()->SetRangeUser(0.0, 1.0);

    // Draw the efficiency plot
    TCanvas cEff = new TCanvas("cEff", "Efficiency Plot", 800, 600);
    cEff.SetGridy();
    cEff.SetGridx();
    effPlot->Draw("AP");  // "AP" for axis and points

    // Save the plot in the output directory as "png" or/and "pdf"
    cEff.SaveAs((saveDir+hName+".png").c_str());
    cEff.SaveAs((saveDir+hName+".pdf").c_str());
}


// For multiple histograms Test
void plotEffWheelStation( std::string hName,
                          std::initializer_list<TFile *> fileList,
                          std::initializer_list<std::string> legendList,
                          std::initializer_list<std::vector<int>> infolist,
                          std::string saveDir )                         
{
    std::vector<TFile *> vFile = fileList;
    std::vector<std::string> vLegend = legendList;
    std::vector<std::vector<int>> vInfo = infolist;

    if (vFile.size() != vLegend.size() || 
        vFile.size() != vInfo.size() || 
        vLegend.size() != vInfo.size() ){
        std::cerr << "Error: Input lists with different sizes" << std::endl;
        return;
    }

    std::vector<TH1F *> hTotal;
    std::vector<TH1F *> hMatched;
    for (const auto& file : vFile) {
        TH1F *histMatched = (TH1F*)file->Get((hName+"_matched").c_str());
        TH1F *histTotal   = (TH1F*)file->Get((hName+"_total").c_str());
        if (!histMatched || !histTotal){
            if (!histTotal)   std::cerr << "Error: Required histograms '" << hName+"_total" << "' not found in root file" << std::endl;
            if (!histMatched) std::cerr << "Error: Required histograms '" << hName+"_matched" << "' not found in root file" << std::endl;
            return;
       } 
       hMatched.push_back(histMatched);
       hTotal.push_back(histTotal);
    }

    // std::cout << "hTotal.size(): " << hTotal.size()<< std::endl;
    // std::cout << "hMatched.size(): " << hMatched.size()<< std::endl;

    // Draw the efficiency plot
    TCanvas cEff = new TCanvas("cEff", "Efficiency Plot", 800, 600);
    cEff.SetGridy();
    // cEff.SetGridx();

    // Create the efficiency plot
    std::vector<TEfficiency *> effPlots;
    for (size_t iHist = 0; iHist < hTotal.size(); ++iHist) {
        TEfficiency* effPlot = new TEfficiency(*hMatched[iHist], *hTotal[iHist]);
        if (!effPlot) std::cerr << "Error: TEfficiency* construction problem" << std::endl;

        effPlot->SetName( hName.c_str() );  // Convert to const char*
        // Style the efficiency plot
        effPlot->SetLineColor(vInfo[iHist][0]);
        effPlot->SetMarkerColor(vInfo[iHist][0]);
        effPlot->SetMarkerStyle(vInfo[iHist][1]);

        TString originalTitle = hTotal[iHist]->GetTitle();
        effPlot->SetTitle(originalTitle);

        effPlots.push_back(effPlot);
    }

    // std::cout << "effPlots.size(): " << effPlots.size()<< std::endl;

    effPlots[0]->Draw("AP"); // "AP" for axis and points
    for (size_t iHist = 1; iHist < effPlots.size(); ++iHist) {
        effPlots[iHist]->Draw("P SAME");
    }

    gPad->Update(); 
    effPlots[0]->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.0,1.005); // Eff  all
    effPlots[0]->GetPaintedGraph()->GetXaxis()->SetLabelSize(0);  // Remove labels completely

    TText *text;
    text = new TText(0.76,0.91,"PU 200 (14 TeV)");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.03);
    text->Draw();

    TLatex latex;
    latex.SetNDC(); // Use NDC (normalized device coordinates)
    // latex.SetTextAlign(22); // Centered alignment
    latex.SetTextSize(0.05); // Set text size
    latex.DrawLatex(0.1,0.91, "CMS ");  // (#it{...} makes the text italic)
    latex.SetTextSize(0.035);
    latex.DrawLatex(0.18,0.91, "#it{Phase-2 Simulation Preliminary}");  // (#it{...} makes the text italic)

    // Draw new label information
    std::vector<std::string> WheelID = {"-2", "-1", " 0", "+1", "+2", "-2", "-1", " 0", "+1", "+2","-2", "-1", " 0", "+1", "+2","-2", "-1", " 0", "+1", "+2"};
    std::vector<std::string> StationID = {"MB1", "MB2", "MB3", "MB4"};
    latex.SetTextSize(0.03);
    double xcoord = 0.13;
    int iMB = 0;
    for (size_t i = 0; i < WheelID.size(); ++i) {
        latex.DrawLatex(xcoord, 0.07, WheelID[i].c_str());

        if ( WheelID[i] == " 0"){
            latex.DrawLatex(xcoord, 0.04, StationID[iMB].c_str());
            iMB++;
        }

        xcoord = xcoord + 0.0356;
    }

    // Get coordinates from the points the the plot
    std::vector<double> pointXcoords;
    for (int bin = 1; bin <= hTotal[0]->GetNbinsX(); bin++) {
        double x = hTotal[0]->GetBinCenter(bin);
        if ( bin == 1 || bin == hTotal[0]->GetNbinsX() ) continue;
        pointXcoords.push_back(x);
        // double y = hTotal1->GetBinContent(bin);
        // std::cout << "Bin " << bin << ": x = " << x << ", y = " << y << std::endl;
    }

    // Draw vertical lines in the canvas
    for (size_t i = 0; i < pointXcoords.size(); ++i) {
        double x[2] = {pointXcoords[i], pointXcoords[i]};  // Same x coordinate
        double y[2] = {0, hTotal[0]->GetMaximum()};  // From bottom to top
        TGraph *vline = new TGraph(2, x, y);
        vline->SetLineColor(kBlack);
        vline->SetLineWidth(1.);
        vline->SetLineStyle(2);
        vline->Draw("L");  // "L" option for line only
    }

    // Draw vertical lines in the canvas
    std::vector<double> divisors = {6, 11, 16};
    for (size_t i = 0; i < divisors.size(); ++i) {
        // double xpos = 6.;
        double x[2] = {divisors[i], divisors[i]};  // Same x coordinate
        double y[2] = {0, hTotal[0]->GetMaximum()};  // From bottom to top
        TGraph *vline = new TGraph(2, x, y);
        vline->SetLineColor(kBlack);
        vline->SetLineWidth(2);
        
        vline->Draw("L");  // "L" option for line only
    }

    // Add legend
    TLegend* leg = new TLegend(0.75, 0.1, 0.9, 0.25);
    for (size_t iHist = 0; iHist < effPlots.size(); ++iHist) {
       leg->AddEntry(effPlots[iHist], vLegend[iHist].c_str(), "lp");
    }
    leg->Draw();
    
    // Save the plot in the output directory as "png" or/and "pdf"
    cEff.SaveAs((saveDir+hName+".png").c_str());
    cEff.SaveAs((saveDir+hName+".pdf").c_str());
    
}


// For multiple histograms Test
void plotEffWheelStationMB1MB2( std::string hName,
                                std::initializer_list<TFile *> fileList,
                                std::initializer_list<std::string> legendList,
                                std::initializer_list<std::vector<int>> infolist,
                                std::string saveDir,
                                std::initializer_list<double> yMinMax = {0.0,1.005} )                         
{
    std::vector<TFile *> vFile = fileList;
    std::vector<std::string> vLegend = legendList;
    std::vector<std::vector<int>> vInfo = infolist;
    std::vector<double> vYMinMax = yMinMax;

    if (vFile.size() != vLegend.size() || 
        vFile.size() != vInfo.size() || 
        vLegend.size() != vInfo.size() ){
        std::cerr << "Error: Input lists with different sizes" << std::endl;
        return;
    }

    std::vector<TH1F *> hTotal;
    std::vector<TH1F *> hMatched;
    for (const auto& file : vFile) {
        TH1F *histMatched = (TH1F*)file->Get((hName+"_matched").c_str());
        TH1F *histTotal   = (TH1F*)file->Get((hName+"_total").c_str());
        if (!histMatched || !histTotal){
            if (!histTotal)   std::cerr << "Error: Required histograms '" << hName+"_total" << "' not found in root file" << std::endl;
            if (!histMatched) std::cerr << "Error: Required histograms '" << hName+"_matched" << "' not found in root file" << std::endl;
            return;
       } 
       hMatched.push_back(histMatched);
       hTotal.push_back(histTotal);
    }

    
    std::vector<TGraphAsymmErrors*> graphs;
    for (size_t iHist = 0; iHist < hTotal.size(); ++iHist) {
        
        int nBins = hMatched[0]->GetNbinsX();
        std::vector<double> x, y, ex_low, ex_high, ey_low, ey_high;

        // for (int i = 1; i <= nBins; ++i) {
        for (int i = 1; i <= 11; ++i) {
            if (i == 1 || i == 22 ) continue;

            double binCenter = hMatched[iHist]->GetXaxis()->GetBinCenter(i);
            double binWidth = hMatched[iHist]->GetXaxis()->GetBinWidth(i) / 2.0;
            double passed = hMatched[iHist]->GetBinContent(i);
            double total = hTotal[iHist]->GetBinContent(i);
            
            // YOU DECIDE what to do with zero-denominator bins
            if (total == 0) {
                // OPTION 1: Show point at 0 with no error (what you requested)
                x.push_back(binCenter);
                y.push_back(0.0);
                ex_low.push_back(binWidth);
                ex_high.push_back(binWidth);
                ey_low.push_back(0.0);
                ey_high.push_back(0.0);
                
                // OPTION 2: Skip entirely (default behavior)
                // continue;
                
                // OPTION 3: Show as undefined (e.g., -1) - will not display
                // x.push_back(binCenter);
                // y.push_back(-1.0);
                // ... etc
            } else {
                // Normal efficiency calculation with Clopper-Pearson errors
                double efficiency = passed / total;
                
                // Wilson score interval or Clopper-Pearson
                // For simplicity, using standard error approximation
                double error = (passed > 0 && passed < total) ? 
                            sqrt(efficiency * (1 - efficiency) / total) : 0;
                
                x.push_back(binCenter);
                y.push_back(efficiency);
                ex_low.push_back(binWidth);
                ex_high.push_back(binWidth);
                ey_low.push_back(error);
                ey_high.push_back(error);
            }
        }

        // Create graph with EXACTLY the points you want
        TGraphAsymmErrors* graph = new TGraphAsymmErrors(x.size(), x.data(), y.data(),
                                                        ex_low.data(), ex_high.data(),
                                                        ey_low.data(), ey_high.data());

        // Remove the horizontal error bars. 
        // Make sense remove them since x-axis is just an enumeration of the wheels.
        for (Int_t k = 0; k < graph->GetN(); ++k) {
            graph->SetPointError(k, 0.0, 0.0, graph->GetErrorYlow(k), graph->GetErrorYhigh(k));
        }
                                            
        graph->SetTitle("");
        graph->SetName( hName.c_str() );
        graph->SetLineColor(vInfo[iHist][0]);
        graph->SetMarkerColor(vInfo[iHist][0]);
        graph->SetMarkerStyle(vInfo[iHist][1]);

        graph->GetXaxis()->SetTitle("Wheels");
        graph->GetYaxis()->SetTitle("Efficiency");
        
        graphs.push_back(graph);
    }

    std::cout << "graphs.size(): " << graphs.size() << std::endl;

    TCanvas cEff = new TCanvas("cEff", "Efficiency Plot", 800, 600);
    cEff.SetGridy();
    // cEff.SetGridx();

   

    graphs[0]->Draw("AP"); // "AP" for axis and points
    for (size_t iHist = 1; iHist < graphs.size(); ++iHist) {
        graphs[iHist]->Draw("P SAME");
    }

    // gPad->Update();
    graphs[0]->GetYaxis()->SetRangeUser(vYMinMax[0],vYMinMax[1]);
    
    TText *text;
    text = new TText(0.76,0.91,"PU 200 (14 TeV)");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.03);
    text->Draw();

    TLatex latex;
    latex.SetNDC(); // Use NDC (normalized device coordinates)
    // latex.SetTextAlign(22); // Centered alignment
    latex.SetTextSize(0.05); // Set text size
    latex.DrawLatex(0.1,0.91, "CMS ");  // (#it{...} makes the text italic)
    latex.SetTextSize(0.035);
    latex.DrawLatex(0.18,0.91, "#it{Phase-2 Simulation Preliminary}");  // (#it{...} makes the text italic)

    // Remove labels completely
    graphs[0]->GetXaxis()->SetLabelSize(0);

    // Draw new label information
    std::vector<std::string> WheelID = {"-2", "-1", " 0", "+1", "+2", "-2", "-1", " 0", "+1", "+2"};
    std::vector<std::string> StationID = {"MB1", "MB2"};
    latex.SetTextSize(0.03);
    double xcoord = 0.16; // 0.19
    int iMB = 0;
    for (size_t i = 0; i < WheelID.size(); ++i) {
        latex.DrawLatex(xcoord, 0.07, WheelID[i].c_str());
        if ( WheelID[i] == " 0"){
            latex.DrawLatex(xcoord, 0.04, StationID[iMB].c_str());
            iMB++;
        }
        xcoord = xcoord + 0.074;  //0.665
    }

    // Get coordinates from the points the the plot
    std::vector<double> pointXcoords;
    for (int bin = 1; bin <= hTotal[0]->GetNbinsX(); bin++) {
        double x = hTotal[0]->GetBinCenter(bin);
        if ( bin == 1 || bin == hTotal[0]->GetNbinsX() ) continue;
        pointXcoords.push_back(x);
        // double y = hTotal1->GetBinContent(bin);
        // std::cout << "Bin " << bin << ": x = " << x << ", y = " << y << std::endl;
    }

    // Draw vertical lines in the canvas
    // for (size_t i = 0; i < pointXcoords.size(); ++i) {
    for (size_t i = 0; i < pointXcoords.size()/2; ++i) {
        double x[2] = {pointXcoords[i], pointXcoords[i]};  // Same x coordinate
        double y[2] = {0, hTotal[0]->GetMaximum()};  // From bottom to top
        TGraph *vline = new TGraph(2, x, y);
        vline->SetLineColor(kGray);
        vline->SetLineWidth(1.);
        vline->SetLineStyle(2);
        vline->Draw("L");  // "L" option for line only
    }

    // Draw vertical lines in the canvas
    // std::vector<double> divisors = {6, 11, 16};
    std::vector<double> divisors = {6};
    for (size_t i = 0; i < divisors.size(); ++i) {
        // double xpos = 6.;
        double x[2] = {divisors[i], divisors[i]};  // Same x coordinate
        double y[2] = {0, hTotal[0]->GetMaximum()};  // From bottom to top
        TGraph *vline = new TGraph(2, x, y);
        vline->SetLineColor(kBlack);
        vline->SetLineWidth(2);
        
        vline->Draw("L");  // "L" option for line only
    }

    // Add legend
    TLegend* leg = new TLegend(0.65, 0.1, 0.9, 0.3);
    for (size_t iHist = 0; iHist < graphs.size(); ++iHist) {
       leg->AddEntry(graphs[iHist], vLegend[iHist].c_str(), "p");
    }
    leg->SetTextSize(0.029);
    leg->Draw();
    
    // Save the plot in the output directory as "png" or/and "pdf"
    cEff.SaveAs((saveDir+hName+".png").c_str());
    cEff.SaveAs((saveDir+hName+".pdf").c_str());
    
} // For multiple histograms Test

void plotEffWheelStationSigma( std::string hName,
                                std::initializer_list<TFile *> fileList, // files
                                std::initializer_list<std::string> legendList, // legends names 
                                std::initializer_list<std::vector<int>> infolist, // legends color and markers 
                                std::string saveDir,
                                std::initializer_list<double> yMinMax = {0.0,1.005} )                         
{
    std::vector<TFile *> vFile = fileList;
    std::vector<std::string> vLegend = legendList;
    std::vector<std::vector<int>> vInfo = infolist;
    std::vector<double> vYMinMax = yMinMax;

    if (vFile.size() != vLegend.size() || 
        vFile.size() != vInfo.size() || 
        vLegend.size() != vInfo.size() ){
        std::cerr << "Error: Input lists with different sizes" << std::endl;
        return;
    }

    std::vector<std::string> wheelTag = {"Wh.-2","Wh.-1","Wh.0","Wh.+1","Wh.+2",};
    std::vector<std::string> chambTag = {"MB1", "MB2", "MB3", "MB4"};

    std::vector<std::vector<double>> vstddev;
    std::vector<std::vector<double>> vstddev_un;

    std::vector<TH2*> vHists;
    // std::vector<TH1F *> hTotal;
    // std::vector<TH1F *> hMatched;
    for (size_t fileIdx = 0; fileIdx < vFile.size(); ++fileIdx) {

        TH2F* hsigma = new TH2F("hsigma", "sigmas; Wheel; #sigma [ns]", 22, 0, 22, 200, 0, 3.5); 

        std::vector<double> temp_stddev;
        std::vector<double> temp_stddev_un;
        for (const auto & chamb : chambTag) {
            for (const auto & wheel : wheelTag) {
                std::string wh = wheel;  
                wh = wh.erase(1, 2); // Removes "h.": "Wh.-2"→ "W-2"
                std::string hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";

                TH1F *hist = (TH1F*)vFile[fileIdx]->Get( hName.c_str() );
                if (!hist){
                    std::cerr << "Error: Required histograms '" << hName+"_total" << "' not found in root file" << std::endl;
                    return;
                } 

                // Get the standard deviation of each histogram
                double stddev = hist->GetStdDev();
                double N = hist->GetEntries(); // Get the number of entries (N)
                double uncertainty = stddev / std::sqrt(2 * N);  // Calculate the uncertainty of the standard deviation

                int station = 0;
                if (chamb == "MB1" ) station = 1;
                else if (chamb == "MB2" ) station = 2;
                else if (chamb == "MB3" ) station = 3;
                else if (chamb == "MB4" ) station = 4;

                int iwheel = 0;
                if (wheel == "Wh.-2" ) iwheel = -2;
                else if (wheel == "Wh.-1" ) iwheel = -1;
                else if (wheel == "Wh.0" ) iwheel = 0;
                else if (wheel == "Wh.+1" ) iwheel = 1;
                else if (wheel == "Wh.+2" ) iwheel = 2;

                int wheelIdx = WheelStationToBins(station, iwheel);
                hsigma->Fill(wheelIdx, stddev);
                // std::cout << "wheelIdx: " << wheelIdx <<  " | stddev: " << stddev << std::endl;

                temp_stddev.push_back(stddev);
                temp_stddev_un.push_back(uncertainty);

            } // chambTag loop
        } // wheelTag loop

        vstddev.push_back(temp_stddev);
        vstddev_un.push_back(temp_stddev_un);
        vHists.push_back(hsigma);
    } //end loop files
    

    std::vector<TGraphAsymmErrors*> graphs;
    for (size_t iHist = 0; iHist < vHists.size(); ++iHist) {

        int nBins = vHists[0]->GetNbinsX();
        std::vector<double> x, y, ex_low, ex_high, ey_low, ey_high;

        int N = vHists[iHist]->GetEntries(); // Get the number of entries (N)

        // Loop in the bins
        for (int i = 1; i <= 11; ++i) {
            if (i == 1 || i == 22 ) continue;

            double binCenter = vHists[iHist]->GetXaxis()->GetBinCenter(i);
            // std::cout << "binCenter:" << binCenter << std::endl;
            double binWidth = vHists[iHist]->GetXaxis()->GetBinWidth(i) / 2.0;

            // double total = vHists[iHist]->GetBinContent(i);
            // std::cout << "total:" << total << std::endl;
            // double total = hTotal[iHist]->GetBinContent(i);

            double total = vstddev[iHist][i-2];
            // std::cout << "total:" << total << std::endl;

            if (total == 0) {
                x.push_back(binCenter);
                ex_low.push_back(0.0); // binWidth
                ex_high.push_back(0.0); // binWidth

                y.push_back(0.0);
                ey_low.push_back(0.0);
                ey_high.push_back(0.0);

            }
            else {
                double stddev_un = vstddev_un[iHist][i-2];
                // std::cout << "uncertainty:" << stddev_un << std::endl;
                
                x.push_back(binCenter);
                ex_low.push_back(0.0); //error
                ex_high.push_back(0.0); //error

                y.push_back(total);
                ey_low.push_back(stddev_un); //error
                ey_high.push_back(stddev_un); //error
            }

        }

        // Create graph with EXACTLY the points you want
        TGraphAsymmErrors* graph = new TGraphAsymmErrors(x.size(), x.data(), y.data(),
                                                        ex_low.data(), ex_high.data(),
                                                        ey_low.data(), ey_high.data());

        // Remove the horizontal error bars. 
        // Make sense remove them since x-axis is just an enumeration of the wheels.
        for (Int_t k = 0; k < graph->GetN(); ++k) {
            graph->SetPointError(k, 0.0, 0.0, graph->GetErrorYlow(k), graph->GetErrorYhigh(k));
        }
                                            
        graph->SetTitle("");
        graph->SetName( hName.c_str() );
        graph->SetLineColor(vInfo[iHist][0]);
        graph->SetMarkerColor(vInfo[iHist][0]);
        graph->SetMarkerStyle(vInfo[iHist][1]);

        graph->GetXaxis()->SetTitle("Wheels");
        graph->GetYaxis()->SetTitle("#sigma [ns]");
        
        graphs.push_back(graph);
    }

    

    std::cout << "graphs.size(): " << graphs.size() << std::endl;

    TCanvas cEff = new TCanvas("cEff", "Efficiency Plot", 800, 600);
    cEff.SetGridy();
    // cEff.SetGridx();
    
    graphs[0]->Draw("AP"); // "AP" for axis and points
    for (size_t iHist = 1; iHist < graphs.size(); ++iHist) {
        graphs[iHist]->Draw("P SAME");
    }
    
    // gPad->Update();
    graphs[0]->GetYaxis()->SetRangeUser(vYMinMax[0],vYMinMax[1]);
    
    TText *text;
    text = new TText(0.76,0.91,"PU 200 (14 TeV)");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.03);
    text->Draw();

    TLatex latex;
    latex.SetNDC(); // Use NDC (normalized device coordinates)
    // latex.SetTextAlign(22); // Centered alignment
    latex.SetTextSize(0.05); // Set text size
    latex.DrawLatex(0.1,0.91, "CMS ");  // (#it{...} makes the text italic)
    latex.SetTextSize(0.035);
    latex.DrawLatex(0.18,0.91, "#it{Phase-2 Simulation Preliminary}");  // (#it{...} makes the text italic)

    // Remove labels completely
    graphs[0]->GetXaxis()->SetLabelSize(0);

    // Draw new label information
    std::vector<std::string> WheelID = {"-2", "-1", " 0", "+1", "+2", "-2", "-1", " 0", "+1", "+2"};
    std::vector<std::string> StationID = {"MB1", "MB2"};
    latex.SetTextSize(0.03);
    double xcoord = 0.16; // 0.19
    int iMB = 0;
    for (size_t i = 0; i < WheelID.size(); ++i) {
        latex.DrawLatex(xcoord, 0.07, WheelID[i].c_str());
        if ( WheelID[i] == " 0"){
            latex.DrawLatex(xcoord, 0.04, StationID[iMB].c_str());
            iMB++;
        }
        xcoord = xcoord + 0.074;  //0.665
    }

    // Get coordinates from the points the the plot
    std::vector<double> pointXcoords;
    for (int bin = 1; bin <= vHists[0]->GetNbinsX(); bin++) {
        // double x = vHists[0]->GetBinCenter(bin); // For 1d histograms
        double x = vHists[0]->GetXaxis()->GetBinCenter(bin); // For 2d histograms

        if ( bin == 1 || bin == vHists[0]->GetNbinsX() ) continue;
        pointXcoords.push_back(x);
        // double y = hTotal1->GetBinContent(bin);
        // std::cout << "Bin " << bin << ": x = " << x << ", y = " << y << std::endl;
    }

    // Draw vertical lines in the canvas for Wheels
    // for (size_t i = 0; i < pointXcoords.size(); ++i) {
    for (size_t i = 0; i < pointXcoords.size()/2; ++i) {
        double x[2] = {pointXcoords[i], pointXcoords[i]};  // Same x coordinate
        // double y[2] = {0, vHists[0]->GetMaximum()};  // From bottom to top
        double y[2] = {0, vYMinMax[1]};  // From bottom to top
        TGraph *vline = new TGraph(2, x, y);
        vline->SetLineColor(kGray);
        vline->SetLineWidth(1.);
        vline->SetLineStyle(2);
        vline->Draw("L");  // "L" option for line only
    }


    // Draw vertical lines in the canvas for divide station regions
    // std::vector<double> divisors = {6, 11, 16};
    std::vector<double> divisors = {6};
    for (size_t i = 0; i < divisors.size(); ++i) {
        // double xpos = 6.;
        double x[2] = {divisors[i], divisors[i]};  // Same x coordinate
        // double y[2] = {0, vHists[0]->GetMaximum()};  // From bottom to top
        double y[2] = {0, vYMinMax[1]};  // From bottom to top
        TGraph *vline = new TGraph(2, x, y);
        vline->SetLineColor(kBlack);
        vline->SetLineWidth(2);
        
        vline->Draw("L");  // "L" option for line only
    }

    // Add legend
    TLegend* leg = new TLegend(0.65, 0.15, 0.9, 0.35);
    for (size_t iHist = 0; iHist < graphs.size(); ++iHist) {
       leg->AddEntry(graphs[iHist], vLegend[iHist].c_str(), "p");
    }
    leg->SetTextSize(0.029);
    leg->Draw();
    
    // Save the plot in the output directory as "png" or/and "pdf"
    cEff.SaveAs((saveDir+hName+"sigma.png").c_str());
    cEff.SaveAs((saveDir+hName+"sigma.pdf").c_str());
    
}

// std::vector<double> temp_stddev;
// for (const auto & wheel : wheelTag) {
//     std::string wh = wheel;  
//     wh = wh.erase(1, 2); // Removes "h.": "Wh.-2"→ "W-2"
//     for (const auto & chamb : chambTag) {
//         std::string hName = "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched";

//         TH1F *hist = (TH1F*)vFile[fileIdx]->Get( hName.c_str() );
//         if (!hist){
//             std::cerr << "Error: Required histograms '" << hName+"_total" << "' not found in root file" << std::endl;
//             return;
//         } 

//         // Get the standard deviation of each histogram
//         double stddev = hist->GetStdDev();

//         temp_stddev.push_back(stddev);

//     }
// }
// vstddev.push_back(temp_stddev);

// For multiples Histograms
void plot_t0_histo( std::string hName,
                    std::initializer_list<TFile *> fileList,
                    std::initializer_list<std::string> legendList,
                    std::initializer_list<std::vector<int>> infolist,
                    std::string str_wh_ch, 
                    std::string saveDir,
                    bool norm=false,
                    bool logYflag=false)  
{

    std::vector<TFile *> vFile = fileList;
    std::vector<std::string> vLegend = legendList;
    std::vector<std::vector<int>> vInfo = infolist;

    if (vFile.size() != vLegend.size() || 
        vFile.size() != vInfo.size() || 
        vLegend.size() != vInfo.size() ){
        std::cerr << "Error: Input lists with different sizes" << std::endl;
        return;
    }

    std::vector<TH1F *> hists;
    std::vector<double> yMax;
    // for (const auto& file : vFile) {
    for (size_t fileIdx = 0; fileIdx < vFile.size(); ++fileIdx) {

        TH1F *hist = (TH1F*)vFile[fileIdx]->Get( hName.c_str() );
        if (!hist){
            std::cerr << "Error: Required histograms '" << hName+"_total" << "' not found in root file" << std::endl;
            return;
        }

        hist->SetTitle(" ");
        hist->GetXaxis()->SetTitle("Time of the TPs associated with prompt muons [ns]");
        hist->GetYaxis()->SetTitle("");

        hist->SetLineColor(vInfo[fileIdx][0]); 
        hist->SetLineStyle(vInfo[fileIdx][1]);
        hist->SetLineWidth(3); 
        // hist2->SetLineStyle(1);9
       
        hist->SetStats(0);  // Remove statistic box

        // Normalize the histogram by its area
        if (norm){
            // Get the sum of bin contents
            double sum = hist->Integral(1, hist->GetNbinsX()); 
            if (sum != 0) {
                double scale = 1.0 / sum;
                hist->Scale(scale);
            }
        }

        hists.push_back(hist);

        double max = hist->GetMaximum();  // Highest bin in hist
        yMax.push_back(max);
    }

    std::vector<std::string> str_stddevs;
    for (size_t iHist = 0; iHist < hists.size(); ++iHist) {
        // Get the standard deviation of each histogram
        double stddev = hists[iHist]->GetStdDev();
        std::cout<< "------------------------------------------------ " << std::endl;
        std::cout<< "   " << str_wh_ch << std::endl;
        double N;
        double uncertainty;
        // std::string str_stddev1 = "#sigma = "+(std::to_string(stddev1)).substr(0, 4);
        N = hists[iHist]->GetEntries();                    // Get the number of entries (N)
        uncertainty = stddev / std::sqrt(2 * N);   // Calculate the uncertainty of the standard deviation
        uncertainty = round(uncertainty*100);
        uncertainty = uncertainty/100;
        // std::cout<< "stddev NoRPC: " <<  (std::to_string(stddev)).substr(0, 4) << std::endl;
        // std::cout<< "uncertainty NoRPC: " <<  uncertainty << std::endl;
        std::string str_stddev = "#sigma = "+(std::to_string(stddev)).substr(0, 4)+ " #pm " +(std::to_string(uncertainty)).substr(0, 4);
        str_stddevs.push_back(str_stddev);
    }
    
    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Histograms from Two Files", 800, 600);
    // Get the standard deviation of each histogram

    // Check which histogram has the highest bin
    double histMax = -999.;
    size_t bestIdx = -1;
    for (size_t iMax = 0; iMax < yMax.size(); ++iMax) {
        if ( yMax[iMax] < histMax) continue;
        histMax = yMax[iMax];
        bestIdx = iMax;
    }

    // Draw Histograms
    hists[bestIdx]->Draw("HIST"); // "AP" for axis and points
    for (size_t iHist = 0; iHist < hists.size(); ++iHist) {
        if (iHist == bestIdx ) continue;
        hists[iHist]->Draw("HIST SAME");
    }

    TText *text = new TText(0.1,0.92,"CMS Preliminary");
    // text->SetNDC(); // To use the canvas coordinates
    // // text->SetTextAlign(31);
    // text->SetTextSize(0.06);
    // text->Draw();

    TLatex latex;
    latex.SetNDC(); // Use NDC (normalized device coordinates)
    // latex.SetTextAlign(22); // Centered alignment
    latex.SetTextSize(0.05); // Set text size
    // latex.DrawLatex(0.1,0.91, "CMS#it{Phase-2 Simulation Preliminary}");  // (#it{...} makes the text italic)
    latex.DrawLatex(0.1,0.91, "CMS ");  // (#it{...} makes the text italic)
    latex.SetTextSize(0.035);
    latex.DrawLatex(0.18,0.91, "#it{Phase-2 Simulation Preliminary}");  // (#it{...} makes the text italic)
    latex.SetTextSize(0.04);
    latex.DrawLatex(0.74,0.8, "p_{T}>20 GeV");  // (#it{...} makes the text italic)

    text = new TText(0.04,0.82,"a.u."); // Events
    text->SetNDC();
    text->SetTextSize(0.05);
    text->SetTextAngle(90);
    if (norm) text->Draw();

    // text = new TText(0.10,0.01, "Time of the TPs associated with prompt muons [ns]");
    // text->SetNDC();
    // text->SetTextSize(0.05);
    // text->Draw();

    // text = new TText(0.68,0.91,"PU 200 (14 TeV)");
    text = new TText(0.76,0.91,"PU 200 (14 TeV)");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.03);
    if (norm) text->Draw();

    text = new TText(0.74,0.85,str_wh_ch.c_str());
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.04);
    if (norm) text->Draw();

    // Create a legend
    TLegend *legend = new TLegend(0.1, 0.65, 0.35, 0.9); // Adjust the coordinates as needed

    for (size_t iLeg = 0; iLeg < hists.size(); ++iLeg) {
        legend->AddEntry(hists[iLeg], vLegend[iLeg].c_str(), "l"); // "DT AM"
        legend->AddEntry(hists[iLeg], str_stddevs[iLeg].c_str(), "");
        legend->SetTextSize(0.03); // Increase the text size in the legend
        legend->Draw(); // Draw the legend
    }

    canvas->SetGridy();
    if (logYflag) canvas->SetLogy();
    text->Draw();
    // if (norm) text2->Draw();

    canvas->Update(); // Update the canvas to display the histograms
    canvas->SaveAs((saveDir+hName+".png").c_str()); // Save the canvas as an image
    canvas->SaveAs((saveDir+hName+".pdf").c_str()); // Save the canvas as PDF

} // For multiples Histograms

void plot_histo(std::string hName,
                std::initializer_list<TFile *> fileList,
                std::initializer_list<std::string> legendList,
                std::initializer_list<std::vector<int>> infolist,
                std::string saveDir,
                bool norm=false,
                bool logYflag=false,
                std::string LegendCoord="TopRight") // TopRight - TopLeft - BottomRight - BottomLeft
{

    std::vector<TFile *> vFile = fileList;
    std::vector<std::string> vLegend = legendList;
    std::vector<std::vector<int>> vInfo = infolist;

    // bool flagExpo = false;

    if (vFile.size() != vLegend.size() || 
        vFile.size() != vInfo.size() || 
        vLegend.size() != vInfo.size() ){
        std::cerr << "Error: Input lists with different sizes" << std::endl;
        return;
    }

    std::vector<TH1F *> hists;
    std::vector<double> yMax;
    std::vector<double> flagExpo;
    // for (const auto& file : vFile) {
    for (size_t fileIdx = 0; fileIdx < vFile.size(); ++fileIdx) {

        TH1F *hist = (TH1F*)vFile[fileIdx]->Get( hName.c_str() );
        if (!hist){
            std::cerr << "Error: Required histograms '" << hName+"_total" << "' not found in root file" << std::endl;
            return;
        } 

        hist->SetTitle(" ");
        // hist->GetXaxis()->SetTitle("");
        // hist->GetYaxis()->SetTitle("");

        hist->SetLineColor(vInfo[fileIdx][0]); 
        hist->SetLineStyle(vInfo[fileIdx][1]);
        hist->SetLineWidth(3); 
        // hist2->SetLineStyle(1);9
       
        hist->SetStats(0);  // Remove statistic box

        // Normalize the histogram by its area
        if (norm){
            // Get the sum of bin contents
            double sum = hist->Integral(1, hist->GetNbinsX()); 
            if (sum != 0) {
                double scale = 1.0 / sum;
                hist->Scale(scale);
            }
        }

      
        // 2. Fetch the axis and its numerical maximum value
        TAxis *yaxis = hist->GetYaxis();
        Double_t ymax = hist->GetMaximum();

        // 3. Compute the scientific exponent mathematically
        Int_t exp = 0;
        if (ymax > 0) {
            exp = (Int_t)floor(log10(ymax));
        }

        // ROOT defaults to using multiples of 3 for engineering notation
        exp = (exp / 3) * 3;
        std::cout << "exp: " << exp <<  std::endl;

        bool flagExpoTemp = false;
        if ( exp > 1) flagExpoTemp = true;

        // if ( flagExpo == true ){

        //     // 4. Hide the native "x 10^N" floating tag 
        //     // yaxis->SetNoExponent(kTRUE);

        //     // 5. Update the title with TLatex script formatting
        //     TString base_title = hist->GetYaxis()->GetTitle();
        //     TString final_title = TString::Format("%s [#times 10^{%d}]", base_title.Data(), exp);
        //     yaxis->SetTitle(final_title);

        //     // // 6. Refresh the canvas layout
        //     // gPad->Modified();
        //     // gPad->Update();
        // }

        double max = hist->GetMaximum();  // Highest bin in hist

        hists.push_back(hist);
        yMax.push_back(max);
        flagExpo.push_back(flagExpoTemp);

    }

    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Histograms from Two Files", 800, 600);
    // Get the standard deviation of each histogram

    
    // Check which histogram has the highest bin
    double histMax = -999.;
    size_t bestIdx = -1;
    for (size_t iMax = 0; iMax < yMax.size(); ++iMax) {
        if ( yMax[iMax] < histMax) continue;
        histMax = yMax[iMax];
        bestIdx = iMax;
    }

    bool flagExpoTotal = true;
    for (size_t iflagExpo = 0; iflagExpo < flagExpo.size(); ++iflagExpo) {
        if ( flagExpo[iflagExpo] == false){
            flagExpoTotal = false;
            break;
        }
    }
    if ( flagExpoTotal == true ){

         // 2. Fetch the axis and its numerical maximum value
        TAxis *yaxis = hists[bestIdx]->GetYaxis();
        Double_t ymax = hists[bestIdx]->GetMaximum();

        // 3. Compute the scientific exponent mathematically
        Int_t exp = 0;
        if (ymax > 0) {
            exp = (Int_t)floor(log10(ymax));
        }

        // ROOT defaults to using multiples of 3 for engineering notation
        exp = (exp / 3) * 3;
        std::cout << "exp: " << exp <<  std::endl;

        // 5. Update the title with TLatex script formatting
        TString base_title = hists[bestIdx]->GetYaxis()->GetTitle();
        TString final_title = TString::Format("%s [#times 10^{%d}]", base_title.Data(), exp);
        // yaxis->SetTitle(final_title);
        hists[bestIdx]->GetYaxis()->SetTitle(final_title);

        // // 6. Refresh the canvas layout
        // gPad->Modified();
        // gPad->Update();
    }

    // Draw Histograms
    hists[bestIdx]->Draw("HIST"); // "AP" for axis and points
    for (size_t iHist = 0; iHist < hists.size(); ++iHist) {
        if (iHist == bestIdx ) continue;
        hists[iHist]->Draw("HIST SAME");
    }

    // Important: Move the exponent fom y-axis
    gPad->Update();  
    // TGaxis::SetExponentOffset(-0.07, 0.01, "y");
    // TGaxis::SetExponentOffset(-0.055, -0.04, "y");
    // TGaxis::SetExponentOffset(-0.09, 0.01, "y");
    // TGaxis::SetMaxDigits(3);
    TGaxis::SetExponentOffset(-0.5, 0.01, "y"); // To put out of Canvas


    TText *text = new TText(0.1,0.92,"CMS Preliminary");

    TLatex latex;
    latex.SetNDC(); // Use NDC (normalized device coordinates)
    latex.SetTextSize(0.05); // Set text size
    latex.DrawLatex(0.1,0.91, "CMS ");
    latex.SetTextSize(0.035);
    latex.DrawLatex(0.18,0.91, "#it{Phase-2 Simulation Preliminary}"); 
    latex.SetTextSize(0.04);

    text = new TText(0.04,0.82,"a.u."); // Events
    text->SetNDC();
    text->SetTextSize(0.05);
    text->SetTextAngle(90);
    if (norm) text->Draw();

    text = new TText(0.75,0.91,"PU 200 (14 TeV)");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.03);
    text->Draw();

    // Create a legend
    TLegend* legend = new TLegend(0.73, 0.75, 0.9, 0.9); // Adjust the coordinates as needed

    if ( LegendCoord == "BottomRight"){
        legend = new TLegend(0.73, 0.1, 0.9, 0.25); // Adjust the coordinates as needed
    }

    for (size_t iLeg = 0; iLeg < hists.size(); ++iLeg) {
        legend->AddEntry(hists[iLeg], vLegend[iLeg].c_str(), "l"); // "DT AM"
        legend->SetTextSize(0.02); // Increase the text size in the legend
        legend->Draw(); // Draw the legend
    }

    canvas->SetGridy();
    if (logYflag) canvas->SetLogy();

    canvas->Update(); // Update the canvas to display the histograms
    canvas->SaveAs((saveDir+hName+".png").c_str()); // Save the canvas as an image
    canvas->SaveAs((saveDir+hName+".pdf").c_str()); // Save the canvas as PDF

    delete canvas;

}