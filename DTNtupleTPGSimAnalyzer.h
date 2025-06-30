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
        std::cerr << "Error: Required histograms not found!" << std::endl;
        return;
    }

    // Create the efficiency plot
    TEfficiency* effPlot = new TEfficiency(*hMatched, *hTotal);
    effPlot->SetName( hName.c_str() );  // Convert to const char*
    effPlot->SetTitle( (hName+"; Sector ; Efficiency").c_str());
    
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
    std::cout<< "uncertainty NoRPC: " <<  uncertainty1 << std::endl;
    std::string str_stddev1 = "#sigma = "+(std::to_string(stddev1)).substr(0, 4)+ "#pm" +(std::to_string(uncertainty1)).substr(0, 4);

    // std::string str_stddev2 = "#sigma = "+(std::to_string(stddev2)).substr(0, 4);
    N = hist2->GetEntries();
    uncertainty2 = stddev2 / std::sqrt(2 * N);
    uncertainty2 = round(uncertainty2*100);
    uncertainty2 = uncertainty2/100;
    std::cout<< "uncertainty RPC  : " <<  uncertainty2 << std::endl;
    std::string str_stddev2 = "#sigma = "+(std::to_string(stddev2)).substr(0, 4)+ "#pm" +(std::to_string(uncertainty2)).substr(0, 4);

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
    TLegend *legend = new TLegend(0.13, 0.5, 0.35, 0.85); // Adjust the coordinates as needed
    legend->AddEntry(hist1,"DT AM", "l");
    legend->AddEntry(hist1, str_stddev1.c_str(), "");
    legend->AddEntry(hist2, "DT AM w/ RPC", "l");
    legend->AddEntry(hist2, str_stddev2.c_str(), "");
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