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





bool fileExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

bool checkFilesInDirectory(const std::vector<std::string>& filenames, 
                           const std::string& directory) {
    bool allExist = true;
    
    for (const auto& filename : filenames) {
        std::string fullPath = directory + filename;
        
        if (fileExists(fullPath)) {
            std::cout << "✓ Found: " << fullPath << std::endl;
        } else {
            std::cout << "✗ Missing: " << fullPath << std::endl;
            allExist = false;
        }
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
                std::string saveDir ) 
{

    // Check if histograms exist
    if (!hMatched1 || !hTotal1 || !hMatched2 || !hTotal2 ) {
        std::cerr << "Error: Required histograms " << hName  << " not found!" << std::endl;
        return;
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

    // effPlot1->GetYaxis()->SetRangeUser(0.0, 1.);  // Y-axis from 0.0 to 1.2
    // effPlot2->GetYaxis()->SetRangeUser(0.0, 1.);  // Y-axis from 0.0 to 1.2
    
    // effPlot->GetYaxis()->SetRangeUser(0.0, 1.0);
    // TGraphAsymmErrors* graph2 = effPlot2->GetPaintedGraph();
    // if (graph2) {
    //     graph2->GetYaxis()->SetRangeUser(0.0, 1.2);
    // }
    
    // Draw the efficiency plot
    TCanvas cEff = new TCanvas("cEff", "Efficiency Plot", 800, 600);
    cEff.SetGridy();
    cEff.SetGridx();
    effPlot2->Draw("AP");  // "AP" for axis and points


    
    effPlot1->Draw("P SAME");  // "AP" for axis and points
    // effPlot3->Draw("AP SAME");  // "AP" for axis and points
    // effPlot4->Draw("AP SAME");  // "AP" for axis and points
    
    gPad->Update();
    effPlot2->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.,1.005);

    // Then set the range using the pad
    gPad->Modified();
    gPad->Update();
    gPad->GetFrame()->SetY1(0.0);    // Bottom of Y-axis
    gPad->GetFrame()->SetY2(1.2);    // Top of Y-axis


    // Add legend
    // TLegend* leg = new TLegend(0.75, 0.1, 0.9, 0.25);
    TLegend* leg = new TLegend(0.75, 0.75, 0.9, 0.9);
    leg->AddEntry(effPlot1, "AM", "lp");
    leg->AddEntry(effPlot2, "AM+RPC", "lp");
    leg->Draw();

    // Save the plot in the output directory as "png" or/and "pdf"
    cEff.SaveAs((saveDir+hName+".png").c_str());
    cEff.SaveAs((saveDir+hName+".pdf").c_str());


    
}




void plot_t0_histograms(   TH1F *hist1, 
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

    // Get the standard deviation of each histogram
    double stddev1 = hist1->GetStdDev();
    double stddev2 = hist2->GetStdDev();

    // stddev1 = std::round(stddev1*100)/100;
    // stddev2 = std::round(stddev2*100)/100;

    // // Extract the first four characters
    // std::string firstFourChars = originalString.substr(0, 4);
    std::cout<< "------------------------------------------------ " << std::endl;
    std::cout<< "   " << str_leg << std::endl;


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


void plot_BX_histograms(   TH1F *hist1, 
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

    // Get the standard deviation of each histogram
    double stddev1 = hist1->GetStdDev();
    double stddev2 = hist2->GetStdDev();

    // stddev1 = std::round(stddev1*100)/100;
    // stddev2 = std::round(stddev2*100)/100;

    // // Extract the first four characters
    // std::string firstFourChars = originalString.substr(0, 4);
    std::cout<< "------------------------------------------------ " << std::endl;
    std::cout<< "   " << str_leg << std::endl;


    // double N;
    // double uncertainty1;
    // double uncertainty2;
    // // std::string str_stddev1 = "#sigma = "+(std::to_string(stddev1)).substr(0, 4);
    // N = hist1->GetEntries();                    // Get the number of entries (N)
    // uncertainty1 = stddev1 / std::sqrt(2 * N);   // Calculate the uncertainty of the standard deviation
    // uncertainty1 = round(uncertainty1*100);
    // uncertainty1 = uncertainty1/100;
    // std::cout<< "stddev NoRPC: " <<  (std::to_string(stddev1)).substr(0, 4) << std::endl;
    // std::cout<< "uncertainty NoRPC: " <<  uncertainty1 << std::endl;
    // std::string str_stddev1 = "#sigma = "+(std::to_string(stddev1)).substr(0, 4)+ "#pm" +(std::to_string(uncertainty1)).substr(0, 4);

    // // std::string str_stddev2 = "#sigma = "+(std::to_string(stddev2)).substr(0, 4);
    // N = hist2->GetEntries();
    // uncertainty2 = stddev2 / std::sqrt(2 * N);
    // uncertainty2 = round(uncertainty2*100);
    // uncertainty2 = uncertainty2/100;
    // std::cout<< "stddev RPC: " <<  (std::to_string(stddev2)).substr(0, 4) << std::endl;
    // std::cout<< "uncertainty RPC  : " <<  uncertainty2 << std::endl;
    // std::string str_stddev2 = "#sigma = "+(std::to_string(stddev2)).substr(0, 4)+ "#pm" +(std::to_string(uncertainty2)).substr(0, 4);

    // // Time improvement calculations

    // double delta = (stddev1 - stddev2);
    // double improvement = delta*100/ stddev1;
    // double sigImp = (uncertainty1-uncertainty2)*100/uncertainty1;
    // double sigDelta = sqrt( pow(uncertainty1,2) + pow(uncertainty2,2) );
    // double zScore = delta/sigDelta;
    // std::cout<< "delta: " <<  delta << std::endl;
    // std::cout<< "Improvement: " <<  improvement <<  " %" << std::endl;
    // std::cout<< "Uncertainty Improvement: " <<  sigImp <<  " %" << std::endl;
    // std::cout<< "Segma Delta (Combined Uncertainty): " <<  sigDelta << std::endl;
    // std::cout<< "Z (Z Score): " <<  zScore << "  (If Z > 2, the difference is statistically significant.)" <<  std::endl;
    // std::cout<< "& $" <<  (std::to_string(stddev1)).substr(0, 4) << "\\pm" << (std::to_string(uncertainty1)).substr(0, 4) 
    //                 << "$ & $" << (std::to_string(stddev2)).substr(0, 4) << "\\pm" << (std::to_string(uncertainty2)).substr(0, 4) 
    //                 << "$ & " <<  improvement << " & " << sigImp << " & " << zScore << std::endl;
    // std::cout<< "------------------------------------------------ " << std::endl;

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
    TLegend *legend = new TLegend(0.13, 0.5, 0.35, 0.85); // Adjust the coordinates as needed
    legend->AddEntry(hist1,"DT AM", "l");
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

    // // // Create a legend
    TLegend *legend = new TLegend(0.65, 0.7, 0.87, 0.85); // Adjust the coordinates as needed
    // TLegend *legend = new TLegend(0.13, 0.5, 0.35, 0.85); // Adjust the coordinates as needed
    legend->AddEntry(hist1,"DT AM", "l");
    // legend->AddEntry(hist1, (std::to_string(N1)).c_str(), "");
    legend->AddEntry(hist2, "DT AM w/ RPC", "l");
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