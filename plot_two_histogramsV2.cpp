#include <iostream>
#include <string>
#include <iomanip> // For std::setprecision


#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TText.h>
#include <TLine.h>
#include <TLatex.h>



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

void plot_two_histograms_function2(  TH1F *hist1, TH1F *hist2, 
                                    std::string str_name,
                                     std::string str_Xaxis,
                                    std::string str_leg = "",
                                    bool norm=false,
                                    bool logYflag=false) {

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

    double N;
    double uncertainty;
    // std::string str_stddev1 = "#sigma = "+(std::to_string(stddev1)).substr(0, 4);
    N = hist1->GetEntries();                    // Get the number of entries (N)
    uncertainty = stddev1 / std::sqrt(2 * N);   // Calculate the uncertainty of the standard deviation
    uncertainty = round(uncertainty*100);
    uncertainty = uncertainty/100;
    std::cout<< "uncertainty 1: " <<  uncertainty << std::endl;

    std::string str_stddev1 = "#sigma = "+(std::to_string(stddev1)).substr(0, 4)+ "#pm" +(std::to_string(uncertainty)).substr(0, 4);

    // std::string str_stddev2 = "#sigma = "+(std::to_string(stddev2)).substr(0, 4);
    N = hist2->GetEntries();
    uncertainty = stddev2 / std::sqrt(2 * N);
    uncertainty = round(uncertainty*100);
    uncertainty = uncertainty/100;
    std::cout<< "uncertainty 2: " <<  uncertainty << std::endl;
    

    std::string str_stddev2 = "#sigma = "+(std::to_string(stddev2)).substr(0, 4)+ "#pm" +(std::to_string(uncertainty)).substr(0, 4);

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

    // text = new TText(0.6,0.91,"Normalized");
    // text->SetNDC(); // To use the canvas coordinates
    // // text->SetTextAlign(31);
    // text->SetTextSize(0.03);
    // if (norm) text->Draw();

    text = new TText(0.68,0.91,"PU 200 (14 TeV)");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.045);
    if (norm) text->Draw();


    text = new TText(0.74,0.85,str_leg.c_str());
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.05);
    if (norm) text->Draw();

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
    canvas->SaveAs(("DTNtupleTPGSimAnalyzer_Efficiency/t0/"+str_name+".png").c_str()); // Save the canvas as an image
    canvas->SaveAs(("DTNtupleTPGSimAnalyzer_Efficiency/t0/"+str_name+".pdf").c_str()); // Save the canvas as PDF

}

void plot_two_histogramsV2() {

    // Open the two ROOT files
    TFile *file1 = TFile::Open("DTNtupleTPGSimAnalyzer_Efficiency/noRPC/DTNtupleTPGSimAnalyzer_Efficiency.root");
    TFile *file2 = TFile::Open("DTNtupleTPGSimAnalyzer_Efficiency/RPC/DTNtupleTPGSimAnalyzer_Efficiency.root");

    if (!file1 || !file2) {
        std::cout << "Error: Could not open one or both files!" << std::endl;
        return;
    }

    // std::vector<std::string> algoTag  = {"AM", "AM+RPC", "Ph1"};
    // std::vector<std::string> totalTag = {"matched", "total"};
    std::vector<std::string> chambTag = {"MB1", "MB2", "MB3", "MB4"};
    std::vector<std::string> wheelTag = {"Wh.-2","Wh.-1","Wh.0","Wh.+1","Wh.+2",};

    TH1F *hist1;
    TH1F *hist2;

    // ----------------------------------------------------------
    // ----Time of the TPs associated with prompt muons [ns]-----
    // ----------------------------------------------------------
    for (const auto & chamb : chambTag) {
        for (const auto & wheel : wheelTag) {
            
            hist1 = (TH1F*)file1->Get(("hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched").c_str());
            hist2 = (TH1F*)file2->Get(("hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched").c_str());

            plot_two_histograms_function2( hist1, hist2, "hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched", "Time of the TPs associated with prompt muons [ns]", (wheel+" "+chamb).c_str(), true);

            // m_plots["hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched"] = new TH1D( ("hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched").c_str(),
            // ("hPh2TpgPhiEmuAmT0"+wheel+chamb+"_matched; Time of the TPs associated with prompt muons [ns]; Entries").c_str(), 27, -10, 10);

        }
    }


    std::cout << "--------------------------------" << std::endl;
    std::cout << "END PROGRAM" << std::endl;
    std::cout << "--------------------------------" << std::endl;

}