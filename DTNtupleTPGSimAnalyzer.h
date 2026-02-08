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


class BarrelGeo {  // The class
  private:  // Access specifier
    std::vector<std::vector<double>> barrel_geometry; // Attribute

  public:
    BarrelGeo() { // Constructor
        
    }
  
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
        std::cerr << "Error: Could not retrieve one or both histograms!" << std::endl;
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

void plot_eff_fake_rate(  std::string hName,
                TH1F *hMatched1, 
                TH1F *hTotal1,
                TH1F *hMatched2, 
                TH1F *hTotal2,
                std::string str_leg = "",
                std::string saveDir = "") 
{

    // Check if histograms exist
    if (!hMatched1 || !hTotal1 || !hMatched2 || !hTotal2 ) {
        std::cerr << "Error: Required histograms " << hName  << " not found!" << std::endl;
        return;
    }
    
    // Get coordinates from the points the the plot
    std::vector<double> pointXcoords;
    for (int bin = 1; bin <= hTotal1->GetNbinsX(); bin++) {
        double x = hTotal1->GetBinCenter(bin);
        if ( bin == 1 || bin == hTotal1->GetNbinsX() ) continue;
        pointXcoords.push_back(x);
        // double y = hTotal1->GetBinContent(bin);
        // std::cout << "Bin " << bin << ": x = " << x << ", y = " << y << std::endl;
    }


    // Create the efficiency plot
    TEfficiency* effPlot1 = new TEfficiency(*hMatched1, *hTotal1);
    effPlot1->SetName( hName.c_str() );  // Convert to const char*
    // Style the efficiency plot
    effPlot1->SetLineColor(kRed);
    effPlot1->SetMarkerColor(kRed);
    effPlot1->SetMarkerStyle(20);

    TEfficiency* effPlot2 = new TEfficiency(*hMatched2, *hTotal2);
    effPlot2->SetName( hName.c_str() );  // Convert to const char*
    // Style the efficiency plot
    effPlot2->SetLineColor(kBlue);
    effPlot2->SetMarkerColor(kBlue);
    effPlot2->SetMarkerStyle(21);


    TString originalTitle = hTotal1->GetTitle();
    effPlot1->SetTitle(originalTitle);
    effPlot2->SetTitle(originalTitle);

    // Draw the efficiency plot
    TCanvas cEff = new TCanvas("cEff", "Efficiency Plot", 800, 600);
    cEff.SetGridy();
    // cEff.SetGridx();
    effPlot2->Draw("AP");  // "AP" for axis and points
    effPlot1->Draw("P SAME");  // "AP" for axis and points
    
    gPad->Update();

    //Flag all - 0
    effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.0,1.005); // Eff  all
    // effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.97,1.01); // Eff by sector
    // effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.6,1.1); //Fake rate not matched
    // effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.0,0.66); // Fake rate over Total


    // effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.98,1); // Fake rate over Total


    //Flag 10
    // effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.988,1.005); // Eff  all
    // effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.97,1.01); // Eff by sector
    // effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.6,1.1); //Fake rate not matched
    // effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.0,0.66); // Fake rate over Total

    //Flag 1
    // effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.8,1.1); // Eff  all
    // effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.4,1.2); // Eff by sector
    // effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.6,1.1); //Fake rate not matched
    // effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.0,0.66); // Fake rate over Total


    // Calculate combined Y-range to show ALL points
    // double ymin = 1.0;
    // double ymax = 0.0;
    
    // // Check both efficiencies for min/max values including errors
    // for (int bin = 1; bin <= effPlot1->GetTotalHistogram()->GetNbinsX(); ++bin) {
    //     if (effPlot1->GetEfficiency(bin) > 0) {
    //         ymin = std::min(ymin, effPlot1->GetEfficiency(bin) - effPlot1->GetEfficiencyErrorLow(bin));
    //     }
    //     if (effPlot1->GetEfficiency(bin) > 0) {
    //         ymin = std::min(ymin, effPlot1->GetEfficiency(bin) - effPlot1->GetEfficiencyErrorLow(bin));
    //     }
    //     ymax = std::max(ymax, effPlot1->GetEfficiency(bin) + effPlot1->GetEfficiencyErrorUp(bin));
    //     ymax = std::max(ymax, effPlot2->GetEfficiency(bin) + effPlot1->GetEfficiencyErrorUp(bin));
    // }

    // std::cout << "ymin: " << ymin << std::endl;
    // std::cout << "ymax: " << ymax << std::endl;
    
    // Add padding
    // ymin = std::max(0.0, ymin - 0.05);
    // ymax = std::min(1.05, ymax + 0.05);
    
    // effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(ymin*0.99,ymax*1.04);

    // effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(ymin,ymax);


    // Calculate the actual data range
    // double data_ymin = 1.0;
    // double data_ymax = 0.0;
    
    // for (int bin = 1; bin <= effPlot1->GetTotalHistogram()->GetNbinsX(); ++bin) {
    //     data_ymin = std::min(data_ymin, effPlot1->GetEfficiency(bin) - effPlot1->GetEfficiencyErrorLow(bin));
    //     data_ymax = std::max(data_ymax, effPlot1->GetEfficiency(bin) + effPlot1->GetEfficiencyErrorUp(bin));
    //     data_ymin = std::min(data_ymin, effPlot2->GetEfficiency(bin) - effPlot2->GetEfficiencyErrorLow(bin));
    //     data_ymax = std::max(data_ymax, effPlot2->GetEfficiency(bin) + effPlot2->GetEfficiencyErrorUp(bin));
    // }
    
    // // Add extra space at the top for the legend
    // double legend_space = 0.15 * (data_ymax - data_ymin); // 15% extra space
    // double ymin = std::max(0.0, data_ymin - 0.05);
    // double ymax = data_ymax + legend_space;
    
    // effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(ymin, ymax);


    effPlot2->GetPaintedGraph()->GetXaxis()->SetLabelSize(0);  // Remove labels completely

    TText *text;
    text = new TText(0.74,0.91,"PU 200 (14 TeV)");
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
    latex.DrawLatex(0.18,0.91, "#it{Phase-2 Simulation}");  // (#it{...} makes the text italic)
    
    
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

    // Draw vertical lines in the canvas
    for (size_t i = 0; i < pointXcoords.size(); ++i) {
        double x[2] = {pointXcoords[i], pointXcoords[i]};  // Same x coordinate
        double y[2] = {0, hTotal1->GetMaximum()};  // From bottom to top
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
        double y[2] = {0, hTotal1->GetMaximum()};  // From bottom to top
        TGraph *vline = new TGraph(2, x, y);
        vline->SetLineColor(kBlack);
        vline->SetLineWidth(2);
        
        vline->Draw("L");  // "L" option for line only
    }
    
    // Add legend
    // TLegend* leg = new TLegend(0.75, 0.1, 0.9, 0.25);
    TLegend* leg = new TLegend(0.75, 0.75, 0.9, 0.9);
    leg->AddEntry(effPlot1, str_leg.c_str(), "lp"); // "DT AM"
    leg->AddEntry(effPlot2, "DT AM+RPC", "lp");
    leg->Draw();

    // Save the plot in the output directory as "png" or/and "pdf"
    cEff.SaveAs((saveDir+hName+".png").c_str());
    cEff.SaveAs((saveDir+hName+".pdf").c_str());


    
}




void plot_t0_histograms(   TH1F *hist1, 
                            TH1F *hist2, 
                            std::string str_name,
                            std::string str_Xaxis,
                            std::string str_wh_ch,
                            std::string str_leg = "",
                            std::string saveDir = "",
                            bool norm=false,
                            bool logYflag=false) 
{

    if (!hist1 || !hist2) {
        std::cerr << "Error: Could not retrieve one or both histograms!" << std::endl;
        return;
    }

    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Histograms from Two Files", 800, 600);

    // Get the standard deviation of each histogram
    double stddev1 = hist1->GetStdDev();
    double stddev2 = hist2->GetStdDev();

    // stddev1 = std::round(stddev1*100)/100;
    // stddev2 = std::round(stddev2*100)/100;

    // // Extract the first four characters
    // std::string firstFourChars = originalString.substr(0, 4);
    std::cout<< "------------------------------------------------ " << std::endl;
    std::cout<< "   " << str_wh_ch << std::endl;


    double N;
    double uncertainty1;
    double uncertainty2;
    // std::string str_stddev1 = "#sigma = "+(std::to_string(stddev1)).substr(0, 4);
    N = hist1->GetEntries();                    // Get the number of entries (N)
    uncertainty1 = stddev1 / std::sqrt(2 * N);   // Calculate the uncertainty of the standard deviation
    uncertainty1 = round(uncertainty1*100);
    uncertainty1 = uncertainty1/100;
    std::cout<< "stddev NoRPC: " <<  (std::to_string(stddev1)).substr(0, 4) << std::endl;
    std::cout<< "uncertainty NoRPC: " <<  uncertainty1 << std::endl;
    std::string str_stddev1 = "#sigma = "+(std::to_string(stddev1)).substr(0, 4)+ " #pm " +(std::to_string(uncertainty1)).substr(0, 4);

    // std::string str_stddev2 = "#sigma = "+(std::to_string(stddev2)).substr(0, 4);
    N = hist2->GetEntries();
    uncertainty2 = stddev2 / std::sqrt(2 * N);
    uncertainty2 = round(uncertainty2*100);
    uncertainty2 = uncertainty2/100;
    std::cout<< "stddev RPC: " <<  (std::to_string(stddev2)).substr(0, 4) << std::endl;
    std::cout<< "uncertainty RPC  : " <<  uncertainty2 << std::endl;
    std::string str_stddev2 = "#sigma = "+(std::to_string(stddev2)).substr(0, 4)+ " #pm " +(std::to_string(uncertainty2)).substr(0, 4);

    // Time improvement calculations

    double delta = (stddev1 - stddev2);
    double improvement = delta*100/ stddev1;
    double sigImp = (uncertainty1-uncertainty2)*100/uncertainty1;
    double sigDelta = sqrt( pow(uncertainty1,2) + pow(uncertainty2,2) );
    double zScore = delta/sigDelta;
    std::cout<< "delta: " <<  delta << std::endl;
    std::cout<< "Improvement: " <<  improvement <<  " %" << std::endl;
    std::cout<< "Uncertainty Improvement: " <<  sigImp <<  " %" << std::endl;
    std::cout<< "Segma Delta (Combined Uncertainty): " <<  sigDelta << std::endl;
    std::cout<< "Z (Z Score): " <<  zScore << "  (If Z > 2, the difference is statistically significant.)" <<  std::endl;
    std::cout<< "& $" <<  (std::to_string(stddev1)).substr(0, 4) << "\\pm" << (std::to_string(uncertainty1)).substr(0, 4) 
                    << "$ & $" << (std::to_string(stddev2)).substr(0, 4) << "\\pm" << (std::to_string(uncertainty2)).substr(0, 4) 
                    << "$ & " <<  improvement << " & " << sigImp << " & " << zScore << std::endl;
    std::cout<< "------------------------------------------------ " << std::endl;

    hist1->SetTitle(" ");
    hist2->SetTitle(" ");
    hist1->GetXaxis()->SetTitle("");
    hist2->GetXaxis()->SetTitle("");
    hist1->GetYaxis()->SetTitle("");
    hist2->GetYaxis()->SetTitle("");

    // Set different colors for the histograms
    hist1->SetLineColor(kRed);
    hist2->SetLineColor(kBlue);

    // Set Line Width
    hist1->SetLineWidth(3);
    hist2->SetLineWidth(3);

    // Set Line Width
    hist1->SetLineStyle(9);
    hist2->SetLineStyle(1);

    // Remove statistic box
    hist1->SetStats(0);
    hist2->SetStats(0);


    // Normalize the histogram by its area
    if (norm){
        // Get the sum of bin contents
        double sum = hist1->Integral(1, hist1->GetNbinsX()); 
        if (sum != 0) {
            double scale = 1.0 / sum;
            hist1->Scale(scale);
        }
        sum = hist2->Integral(1, hist2->GetNbinsX()); 
        if (sum != 0) {
            double scale = 1.0 / sum;
            hist2->Scale(scale);
        }

        // hist1->SetLineColor(kRed);
        // hist1->SetFillColor(kRed);
        // hist1->SetFillStyle(3006);

        // hist2->SetLineColor(kBlue); // Set colors of histograms
        // hist2->SetFillColor(kBlue);
        // hist2->SetFillStyle(3005); // Set fill style of histograms to transparent
        // vHistograms[j]->GetXaxis()->SetTitle("Bunch Crossing Units [25ns]");  
    }

    hist2->Draw("HIST"); // Draw the second histogram on the same canvas
    hist1->Draw("HIST SAME");  // Draw the first histogram

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
    latex.DrawLatex(0.18,0.91, "#it{Phase-2 Simulation}");  // (#it{...} makes the text italic)
    latex.SetTextSize(0.04);
    latex.DrawLatex(0.74,0.8, "p_{T}>20 GeV");  // (#it{...} makes the text italic)

    text = new TText(0.04,0.82,"a.u."); // Events
    text->SetNDC();
    text->SetTextSize(0.05);
    text->SetTextAngle(90);
    if (norm) text->Draw();

    text = new TText(0.10,0.01, str_Xaxis.c_str());
    // text = new TText(0.50,0.03,"Segment timing [ns]"); str_Xaxis
    text->SetNDC();
    text->SetTextSize(0.05);
    text->Draw();

    text = new TText(0.68,0.91,"PU 200 (14 TeV)");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.04);
    if (norm) text->Draw();


    text = new TText(0.74,0.85,str_wh_ch.c_str());
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.04);
    if (norm) text->Draw();

    // text = new TText(0.74,0.8, "$p_{T}>20$ GeV");
    // text->SetNDC(); // To use the canvas coordinates
    // // text->SetTextAlign(31);
    // text->SetTextSize(0.04);
    // if (norm) text->Draw();

    // // // Create a legend
    TLegend *legend = new TLegend(0.13, 0.6, 0.35, 0.85); // Adjust the coordinates as needed
    legend->AddEntry(hist1,str_leg.c_str(), "l"); // "DT AM"
    legend->AddEntry(hist1, str_stddev1.c_str(), "");
    legend->AddEntry(hist2, "DT AM w/ RPC", "l");
    legend->AddEntry(hist2, str_stddev2.c_str(), "");
    legend->SetTextSize(0.03); // Increase the text size in the legend
    legend->Draw(); // Draw the legend

    canvas->SetGridy();
    if (logYflag) canvas->SetLogy();
    text->Draw();
    // if (norm) text2->Draw();

    canvas->Update(); // Update the canvas to display the histograms
    canvas->SaveAs((saveDir+str_name+".png").c_str()); // Save the canvas as an image
    canvas->SaveAs((saveDir+str_name+".pdf").c_str()); // Save the canvas as PDF

}

void plot_t0_histogramsV2(  TH1F *hist1, 
                            TH1F *hist2,
                            TH1F *hist3, 
                            std::string str_name,
                            std::string str_Xaxis,
                            std::string str_leg = "",
                            std::string saveDir = "",
                            bool norm=false,
                            bool logYflag=false) 
{

    if (!hist1 || !hist2) {
        std::cerr << "Error: Could not retrieve one or both histograms!" << std::endl;
        return;
    }

    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Histograms from Two Files", 800, 600);

    // Get the standard deviation of each histogram
    double stddev1 = hist1->GetStdDev();
    double stddev2 = hist2->GetStdDev();
    double stddev3 = hist3->GetStdDev();

    // stddev1 = std::round(stddev1*100)/100;
    // stddev2 = std::round(stddev2*100)/100;

    // // Extract the first four characters
    // std::string firstFourChars = originalString.substr(0, 4);
    std::cout<< "------------------------------------------------ " << std::endl;
    std::cout<< "   " << str_leg << std::endl;


    double N;
    double uncertainty1;
    double uncertainty2;
    double uncertainty3;
    // std::string str_stddev1 = "#sigma = "+(std::to_string(stddev1)).substr(0, 4);
    N = hist1->GetEntries();                    // Get the number of entries (N)
    uncertainty1 = stddev1 / std::sqrt(2 * N);   // Calculate the uncertainty of the standard deviation
    uncertainty1 = round(uncertainty1*100);
    uncertainty1 = uncertainty1/100;
    std::cout<< "stddev NoRPC: " <<  (std::to_string(stddev1)).substr(0, 4) << std::endl;
    std::cout<< "uncertainty NoRPC: " <<  uncertainty1 << std::endl;
    std::string str_stddev1 = "#sigma = "+(std::to_string(stddev1)).substr(0, 4)+ " #pm " +(std::to_string(uncertainty1)).substr(0, 4);

    // std::string str_stddev2 = "#sigma = "+(std::to_string(stddev2)).substr(0, 4);
    N = hist2->GetEntries();
    uncertainty2 = stddev2 / std::sqrt(2 * N);
    uncertainty2 = round(uncertainty2*100);
    uncertainty2 = uncertainty2/100;
    std::cout<< "stddev RPC: " <<  (std::to_string(stddev2)).substr(0, 4) << std::endl;
    std::cout<< "uncertainty RPC  : " <<  uncertainty2 << std::endl;
    std::string str_stddev2 = "#sigma = "+(std::to_string(stddev2)).substr(0, 4)+ " #pm " +(std::to_string(uncertainty2)).substr(0, 4);

    // std::string str_stddev2 = "#sigma = "+(std::to_string(stddev2)).substr(0, 4);
    N = hist3->GetEntries();
    uncertainty3 = stddev3 / std::sqrt(2 * N);
    uncertainty3 = round(uncertainty3*100);
    uncertainty3 = uncertainty3/100;
    std::cout<< "stddev RPC: " <<  (std::to_string(stddev3)).substr(0, 4) << std::endl;
    std::cout<< "uncertainty RPC  : " <<  uncertainty3 << std::endl;
    std::string str_stddev3 = "#sigma = "+(std::to_string(stddev3)).substr(0, 4)+ " #pm " +(std::to_string(uncertainty3)).substr(0, 4);

    // Time improvement calculations

    double delta = (stddev1 - stddev2);
    double improvement = delta*100/ stddev1;
    double sigImp = (uncertainty1-uncertainty2)*100/uncertainty1;
    double sigDelta = sqrt( pow(uncertainty1,2) + pow(uncertainty2,2) );
    double zScore = delta/sigDelta;
    std::cout<< "delta: " <<  delta << std::endl;
    std::cout<< "Improvement: " <<  improvement <<  " %" << std::endl;
    std::cout<< "Uncertainty Improvement: " <<  sigImp <<  " %" << std::endl;
    std::cout<< "Segma Delta (Combined Uncertainty): " <<  sigDelta << std::endl;
    std::cout<< "Z (Z Score): " <<  zScore << "  (If Z > 2, the difference is statistically significant.)" <<  std::endl;
    std::cout<< "& $" <<  (std::to_string(stddev1)).substr(0, 4) << "\\pm" << (std::to_string(uncertainty1)).substr(0, 4) 
                    << "$ & $" << (std::to_string(stddev2)).substr(0, 4) << "\\pm" << (std::to_string(uncertainty2)).substr(0, 4) 
                    << "$ & " <<  improvement << " & " << sigImp << " & " << zScore << std::endl;
    std::cout<< "------------------------------------------------ " << std::endl;

    hist1->SetTitle("");
    hist2->SetTitle("");
    hist3->SetTitle("");

    // Set different colors for the histograms
    hist1->SetLineColor(kRed);
    hist2->SetLineColor(kBlue);
    hist3->SetLineColor(kBlack);

    // Set Line Width
    hist1->SetLineWidth(3);
    hist2->SetLineWidth(3);
    hist3->SetLineWidth(3);

    // Set Line Width
    hist1->SetLineStyle(9);
    hist2->SetLineStyle(1);
    hist3->SetLineStyle(2);

    // Remove statistic box
    hist1->SetStats(0);
    hist2->SetStats(0);
    hist3->SetStats(0);

    // Normalize the histogram by its area
    if (norm){
        // Get the sum of bin contents
        double sum = hist1->Integral(1, hist1->GetNbinsX()); 
        if (sum != 0) {
            double scale = 1.0 / sum;
            hist1->Scale(scale);
        }
        sum = hist2->Integral(1, hist2->GetNbinsX()); 
        if (sum != 0) {
            double scale = 1.0 / sum;
            hist2->Scale(scale);
        }
        sum = hist3->Integral(1, hist3->GetNbinsX()); 
        if (sum != 0) {
            double scale = 1.0 / sum;
            hist3->Scale(scale);
        }

        // hist1->SetLineColor(kRed);
        // hist1->SetFillColor(kRed);
        // hist1->SetFillStyle(3006);

        // hist2->SetLineColor(kBlue); // Set colors of histograms
        // hist2->SetFillColor(kBlue);
        // hist2->SetFillStyle(3005); // Set fill style of histograms to transparent
        // vHistograms[j]->GetXaxis()->SetTitle("Bunch Crossing Units [25ns]");  
    }

    hist3->Draw("HIST");  // Draw the first histogram
    hist2->Draw("HIST SAME"); // Draw the second histogram on the same canvas
    hist1->Draw("HIST SAME");  // Draw the first histogram

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
    latex.DrawLatex(0.18,0.91, "#it{Phase-2 Simulation}");  // (#it{...} makes the text italic)
    latex.SetTextSize(0.04);
    latex.DrawLatex(0.74,0.8, "p_{T}>20 GeV");  // (#it{...} makes the text italic)

    text = new TText(0.04,0.82,"a.u."); // Events
    text->SetNDC();
    text->SetTextSize(0.05);
    text->SetTextAngle(90);
    if (norm) text->Draw();

    text = new TText(0.10,0.01, str_Xaxis.c_str());
    // text = new TText(0.50,0.03,"Segment timing [ns]"); str_Xaxis
    text->SetNDC();
    text->SetTextSize(0.05);
    text->Draw();

    text = new TText(0.68,0.91,"PU 200 (14 TeV)");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.04);
    if (norm) text->Draw();


    text = new TText(0.74,0.85,str_leg.c_str());
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.04);
    if (norm) text->Draw();

    // text = new TText(0.74,0.8, "$p_{T}>20$ GeV");
    // text->SetNDC(); // To use the canvas coordinates
    // // text->SetTextAlign(31);
    // text->SetTextSize(0.04);
    // if (norm) text->Draw();

    // // // Create a legend
    TLegend *legend = new TLegend(0.13, 0.6, 0.35, 0.85); // Adjust the coordinates as needed
    legend->AddEntry(hist1,"DT AM", "l");
    legend->AddEntry(hist1, str_stddev1.c_str(), "");
    legend->AddEntry(hist2, "DT AM w/ RPC", "l");
    legend->AddEntry(hist2, str_stddev2.c_str(), "");
    legend->AddEntry(hist3, "DT+RPC(updated)", "l");
    legend->AddEntry(hist3, str_stddev3.c_str(), "");
    legend->SetTextSize(0.028); // Increase the text size in the legend
    legend->Draw(); // Draw the legend

    canvas->SetGridy();
    if (logYflag) canvas->SetLogy();
    text->Draw();
    // if (norm) text2->Draw();

    canvas->Update(); // Update the canvas to display the histograms
    canvas->SaveAs((saveDir+str_name+"V2.png").c_str()); // Save the canvas as an image
    canvas->SaveAs((saveDir+str_name+"V2.pdf").c_str()); // Save the canvas as PDF

}


void plot_BX_histograms(TH1F *hist1, 
                        TH1F *hist2, 
                        std::string str_name,
                        std::string str_Xaxis,
                        std::string str_wh_ch,
                        std::string str_leg = "", 
                        std::string saveDir = "",
                        bool norm=false,
                        bool logYflag=false) 
{

    if (!hist1 || !hist2) {
        std::cerr << "Error: Could not retrieve one or both histograms!" << std::endl;
        return;
    }

    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Histograms from Two Files", 800, 600);

    // Get the standard deviation of each histogram
    double stddev1 = hist1->GetStdDev();
    double stddev2 = hist2->GetStdDev();

    // stddev1 = std::round(stddev1*100)/100;
    // stddev2 = std::round(stddev2*100)/100;

    // // Extract the first four characters
    // std::string firstFourChars = originalString.substr(0, 4);

    hist1->SetTitle("");
    hist2->SetTitle("");

    // Set different colors for the histograms
    hist1->SetLineColor(kRed);
    hist2->SetLineColor(kBlue);

    // Set Line Width
    hist1->SetLineWidth(3);
    hist2->SetLineWidth(3);

    // Set Line Width
    hist1->SetLineStyle(9);
    hist2->SetLineStyle(1);

    // Remove statistic box
    hist1->SetStats(0);
    hist2->SetStats(0);


    // Normalize the histogram by its area
    if (norm){
        // Get the sum of bin contents
        double sum = hist1->Integral(1, hist1->GetNbinsX()); 
        if (sum != 0) {
            double scale = 1.0 / sum;
            hist1->Scale(scale);
        }
        sum = hist2->Integral(1, hist2->GetNbinsX()); 
        if (sum != 0) {
            double scale = 1.0 / sum;
            hist2->Scale(scale);
        }

        // hist1->SetLineColor(kRed);
        // hist1->SetFillColor(kRed);
        // hist1->SetFillStyle(3006);

        // hist2->SetLineColor(kBlue); // Set colors of histograms
        // hist2->SetFillColor(kBlue);
        // hist2->SetFillStyle(3005); // Set fill style of histograms to transparent
        // vHistograms[j]->GetXaxis()->SetTitle("Bunch Crossing Units [25ns]");  
    }

    hist2->Draw("HIST"); // Draw the second histogram on the same canvas
    hist1->Draw("HIST SAME");  // Draw the first histogram

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
    latex.DrawLatex(0.18,0.91, "#it{Phase-2 Simulation}");  // (#it{...} makes the text italic)
    latex.SetTextSize(0.04);
    latex.DrawLatex(0.74,0.8, "p_{T}>20 GeV");  // (#it{...} makes the text italic)

    text = new TText(0.04,0.82,"a.u."); // Events
    text->SetNDC();
    text->SetTextSize(0.05);
    text->SetTextAngle(90);
    if (norm) text->Draw();

    text = new TText(0.10,0.01, str_Xaxis.c_str());
    // text = new TText(0.50,0.03,"Segment timing [ns]"); str_Xaxis
    text->SetNDC();
    text->SetTextSize(0.05);
    text->Draw();

    text = new TText(0.68,0.91,"PU 200 (14 TeV)");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.04);
    if (norm) text->Draw();


    text = new TText(0.74,0.85,str_wh_ch.c_str());
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.04);
    if (norm) text->Draw();

    // text = new TText(0.74,0.8, "$p_{T}>20$ GeV");
    // text->SetNDC(); // To use the canvas coordinates
    // // text->SetTextAlign(31);
    // text->SetTextSize(0.04);
    // if (norm) text->Draw();

    // // // Create a legend
    TLegend *legend = new TLegend(0.13, 0.5, 0.35, 0.85); // Adjust the coordinates as needed
    legend->AddEntry(hist1,str_leg.c_str(), "l"); // "DT AM"
    // legend->AddEntry(hist1, str_stddev1.c_str(), "");
    legend->AddEntry(hist2, "DT AM w/ RPC", "l");
    // legend->AddEntry(hist2, str_stddev2.c_str(), "");
    legend->SetTextSize(0.035); // Increase the text size in the legend
    legend->Draw(); // Draw the legend

    canvas->SetGridy();
    if (logYflag) canvas->SetLogy();
    text->Draw();
    // if (norm) text2->Draw();

    canvas->Update(); // Update the canvas to display the histograms
    canvas->SaveAs((saveDir+str_name+".png").c_str()); // Save the canvas as an image
    canvas->SaveAs((saveDir+str_name+".pdf").c_str()); // Save the canvas as PDF

}


void plot_normal_histograms(TH1F *hist1, 
                            TH1F *hist2,
                            std::string str_name,
                            std::string str_Xaxis,
                            std::string str_leg = "",
                            std::string saveDir = "",
                            bool norm=false,
                            bool logYflag=false) 
{

    if (!hist1 || !hist2) {
        std::cerr << "Error: Could not retrieve one or both histograms!" << std::endl;
        return;
    }

    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Histograms from Two Files", 800, 600);

    int N1 = hist1->GetEntries(); // Get the number of entries (N)
    int N2 = hist2->GetEntries();

    double max1 = hist1->GetMaximum();  // Highest bin in h1
    double max2 = hist2->GetMaximum();  // Highest bin in h2
    
    hist1->SetTitle("");
    hist2->SetTitle("");

    // Set different colors for the histograms
    hist1->SetLineColor(kRed);
    hist2->SetLineColor(kBlue);
    // Set Line Width
    hist1->SetLineWidth(3);
    hist2->SetLineWidth(3);
    // Set Line Width
    hist1->SetLineStyle(9);
    hist2->SetLineStyle(1);
    // Remove statistic box
    hist1->SetStats(0);
    hist2->SetStats(0);

    // Normalize the histogram by its area
    if (norm){
        // Get the sum of bin contents
        double sum = hist1->Integral(1, hist1->GetNbinsX()); 
        if (sum != 0) {
            double scale = 1.0 / sum;
            hist1->Scale(scale);
        }
        sum = hist2->Integral(1, hist2->GetNbinsX()); 
        if (sum != 0) {
            double scale = 1.0 / sum;
            hist2->Scale(scale);
        }
    }

    // hist2->Draw("HIST"); // Draw the second histogram on the same canvas
    // hist1->Draw("HIST SAME");  // Draw the first histogram

    if (max1 > max2){
        hist1->Draw("HIST");
        hist2->Draw("HIST SAME");
    }
    else if (max2 > max1){
        hist2->Draw("HIST");
        hist1->Draw("HIST SAME");
    } 
    else{
        hist2->Draw("HIST");
        hist1->Draw("HIST SAME");
    }

    // Important: Move the exponent 
    gPad->Update();  
    TGaxis::SetExponentOffset(-0.07, 0.01, "y");

    TText *text = new TText(0.1,0.92,"CMS Preliminary");

    TLatex latex;
    latex.SetNDC(); // Use NDC (normalized device coordinates)
    latex.SetTextSize(0.05); // Set text size
    latex.DrawLatex(0.1,0.91, "CMS ");  // (#it{...} makes the text italic)
    latex.SetTextSize(0.035);
    latex.DrawLatex(0.18,0.91, "#it{Phase-2 Simulation}");  // (#it{...} makes the text italic)
    latex.SetTextSize(0.04);

    text = new TText(0.04,0.82,"a.u."); // Events
    text->SetNDC();
    text->SetTextSize(0.05);
    text->SetTextAngle(90);
    if (norm) text->Draw();

    text = new TText(0.10,0.01, str_Xaxis.c_str());
    // text = new TText(0.50,0.03,"Segment timing [ns]"); str_Xaxis
    text->SetNDC();
    text->SetTextSize(0.05);
    text->Draw();

    text = new TText(0.74,0.91,"PU 200 (14 TeV)");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.03);
    text->Draw();


    // text = new TText(0.74,0.85,str_leg.c_str());
    // text->SetNDC(); // To use the canvas coordinates
    // // text->SetTextAlign(31);
    // text->SetTextSize(0.04);
    // if (norm) text->Draw();

    // // // Create a legend
    // TLegend *legend = new TLegend(0.65, 0.7, 0.87, 0.85); // Adjust the coordinates as needed 
    TLegend* legend = new TLegend(0.73, 0.75, 0.9, 0.9);
    legend->AddEntry(hist1, str_leg.c_str(), "l"); // "DT AM"
    // legend->AddEntry(hist1, (std::to_string(N1)).c_str(), "");
    legend->AddEntry(hist2, "DT AM+RPC", "l");
    // legend->AddEntry(hist2, (std::to_string(N2)).c_str(), "");
    legend->SetTextSize(0.03); // Increase the text size in the legend
    legend->Draw(); // Draw the legend

    canvas->SetGridy();
    if (logYflag) canvas->SetLogy();
    text->Draw();
    // if (norm) text2->Draw();

    canvas->Update(); // Update the canvas to display the histograms
    canvas->SaveAs((saveDir+str_name+".png").c_str()); // Save the canvas as an image
    canvas->SaveAs((saveDir+str_name+".pdf").c_str()); // Save the canvas as PDF


}


void plot_fakeRate_wheels_histograms(TH1F *hist1, 
                            TH1F *hist2,
                            std::string str_name,
                            std::string str_Xaxis,
                            std::string str_leg = "",
                            std::string saveDir = "",
                            bool norm=false,
                            bool logYflag=false) 
{

    if (!hist1 || !hist2) {
        std::cerr << "Error: Could not retrieve one or both histograms!" << std::endl;
        return;
    }

    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Histograms from Two Files", 800, 600);

    int N1 = hist1->GetEntries(); // Get the number of entries (N)
    int N2 = hist2->GetEntries();

    double max1 = hist1->GetMaximum();  // Highest bin in h1
    double max2 = hist2->GetMaximum();  // Highest bin in h2
    
    // hist1->SetTitle("");
    // hist2->SetTitle("");

    // Change histograms characteristics
    hist1->SetStats(0); // Remove statistic box
    hist1->SetLineColor(kRed);
    hist1->SetLineWidth(1);
    // hist1->SetLineStyle(9);
    hist1->SetMarkerColor(kRed);
    hist1->SetMarkerStyle(20);
    
    hist2->SetStats(0);
    hist2->SetLineColor(kBlue);
    hist2->SetLineWidth(1);
    // hist2->SetLineStyle(1);
    hist2->SetMarkerColor(kBlue);
    hist2->SetMarkerStyle(21);



    // Normalize the histogram by its area
    if (norm){
        // Get the sum of bin contents
        double sum = hist1->Integral(1, hist1->GetNbinsX()); 
        if (sum != 0) {
            double scale = 1.0 / sum;
            hist1->Scale(scale);
        }
        sum = hist2->Integral(1, hist2->GetNbinsX()); 
        if (sum != 0) {
            double scale = 1.0 / sum;
            hist2->Scale(scale);
        }
    }

   
    int FlagHisto = 0;
    if (max1 > max2){
        hist1->Draw("p");
        hist2->Draw("p SAME");
        FlagHisto = 1;
    }
    else if (max2 > max1){
        hist2->Draw("p");
        hist1->Draw("p SAME");
        FlagHisto = 2;
    } 
    else{
        hist2->Draw("p");
        hist1->Draw("p SAME");
        FlagHisto = 2;
    }

    // Important: Move the exponent 
    gPad->Update();  
    TGaxis::SetExponentOffset(-0.07, 0.01, "y");

    hist1->GetXaxis()->SetLabelSize(0);  // Remove labels completely
    hist2->GetXaxis()->SetLabelSize(0);  // Remove labels completely

    // Get coordinates from the points the the plot
    std::vector<double> pointXcoords;
    for (int bin = 1; bin <= hist1->GetNbinsX(); bin++) {
        double x = hist1->GetBinCenter(bin);
        if ( bin == 1 || bin == hist1->GetNbinsX() ) continue;
        pointXcoords.push_back(x);
    }

    // Draw vertical lines in the canvas base on x-cootdinates of the points
    for (size_t i = 0; i < pointXcoords.size(); ++i) {
        double x[2] = {pointXcoords[i], pointXcoords[i]};  // Same x coordinate
        double y[2] = {0,0};
        if (FlagHisto == 1) y[1] = {hist1->GetMaximum()}; // From bottom to top
        if (FlagHisto == 2) y[1] = {hist2->GetMaximum()};
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
        double y[2] = {0,0};
        if (FlagHisto == 1) y[1] = {hist1->GetMaximum()}; // From bottom to top
        if (FlagHisto == 2) y[1] = {hist2->GetMaximum()};
        TGraph *vline = new TGraph(2, x, y);
        vline->SetLineColor(kBlack);
        vline->SetLineWidth(2);
        vline->Draw("L");  // "L" option for line only
    }

    // Draw new label information
    TLatex latex;
    latex.SetNDC();
    std::vector<std::string> WheelID = {"-2", "-1", " 0", "+1", "+2", "-2", "-1", " 0", "+1", "+2","-2", "-1", " 0", "+1", "+2","-2", "-1", " 0", "+1", "+2"};
    std::vector<std::string> StationID = {"MB1", "MB2", "MB3", "MB4"};
    // latex.SetTextSize(0.03);
    // double xcoord = 1.2;
    // int iMB = 0;
    // for (size_t i = 0; i < WheelID.size(); ++i) {
    //     latex.DrawLatex(xcoord, -0.5, WheelID[i].c_str());
    //     if ( WheelID[i] == " 0"){
    //         latex.DrawLatex(xcoord - 0.6, -0.12, StationID[iMB].c_str());
    //         iMB++;
    //     }
    //     xcoord = xcoord + 1.;
    // }

    latex.SetTextSize(0.03);
    double xcoord = 0.14;
    int iMB = 0;
    for (size_t i = 0; i < WheelID.size(); ++i) {
        latex.DrawLatex(xcoord, 0.07, WheelID[i].c_str());

        if ( WheelID[i] == " 0"){
            latex.DrawLatex(xcoord, 0.04, StationID[iMB].c_str());
            iMB++;
        }

        xcoord = xcoord + 0.0365;
    }


    TText *text;
    text = new TText(0.10,0.01, str_Xaxis.c_str());
    // text = new TText(0.50,0.03,"Segment timing [ns]"); str_Xaxis
    text->SetNDC();
    text->SetTextSize(0.05);
    text->Draw();

    text = new TText(0.74,0.91,"PU 200 (14 TeV)");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.03);
    text->Draw();


    text = new TText(0.74,0.85,str_leg.c_str());
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.04);
    if (norm) text->Draw();


    
    // latex.SetNDC(); // Use NDC (normalized device coordinates)
    latex.SetTextSize(0.05); // Set text size
    latex.DrawLatex(0.1,0.91, "CMS ");  // (#it{...} makes the text italic)
    latex.SetTextSize(0.035);
    latex.DrawLatex(0.18,0.91, "#it{Phase-2 Simulation}");  // (#it{...} makes the text italic)
    latex.SetTextSize(0.04);


    // // // Create a legend
    // TLegend *legend = new TLegend(0.65, 0.7, 0.87, 0.85); // Adjust the coordinates as needed 
    TLegend* legend = new TLegend(0.73, 0.75, 0.9, 0.9);
    legend->AddEntry(hist1,"DT AM", "l");
    // legend->AddEntry(hist1, (std::to_string(N1)).c_str(), "");
    legend->AddEntry(hist2, "DT AM+RPC", "l");
    // legend->AddEntry(hist2, (std::to_string(N2)).c_str(), "");
    legend->SetTextSize(0.03); // Increase the text size in the legend
    legend->Draw(); // Draw the legend

    canvas->SetGridy();
    if (logYflag) canvas->SetLogy();

    canvas->Update(); // Update the canvas to display the histograms
    canvas->SaveAs((saveDir+str_name+".png").c_str()); // Save the canvas as an image
    canvas->SaveAs((saveDir+str_name+".pdf").c_str()); // Save the canvas as PDF


}