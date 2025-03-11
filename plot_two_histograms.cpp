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

void plot_two_histograms_function(  TH1F *hist1, TH1F *hist2, 
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

    stddev1 = std::round(stddev1*100)/100;
    stddev2 = std::round(stddev2*100)/100;

    std::string str_stddev1 = "#sigma = "+std::to_string( round(stddev1) );
    std::string str_stddev2 = "#sigma = "+std::to_string(stddev2);

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
    latex.SetTextSize(0.04); // Set text size
    latex.DrawLatex(0.1,0.92, "CMS #it{Phase-2 Simulation Preliminary}");  // (#it{...} makes the text italic)

    text = new TText(0.04,0.82,"a.u."); // Events
    text->SetNDC();
    text->SetTextSize(0.06);
    text->SetTextAngle(90);
    if (norm) text->Draw();

    // text = new TText(0.50,0.03,"Bunch Crossing Units [25ns]"); 
    text = new TText(0.50,0.03, str_Xaxis.c_str());
    text->SetNDC();
    text->SetTextSize(0.05);
    text->Draw();

    // text = new TText(0.6,0.91,"Normalized");
    // text->SetNDC(); // To use the canvas coordinates
    // // text->SetTextAlign(31);
    // text->SetTextSize(0.03);
    // if (norm) text->Draw();

    text = new TText(0.75,0.85,"200 PU");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.05);
    if (norm) text->Draw();


    text = new TText(0.75,0.81,str_leg.c_str());
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.05);
    if (norm) text->Draw();

    // // // Create a legend
    // TLegend *legend = new TLegend(0.13, 0.5, 0.35, 0.85); // Adjust the coordinates as needed
    // legend->AddEntry(hist1,"DT AM", "l");
    // legend->AddEntry(hist1, str_stddev1.c_str(), "");
    // legend->AddEntry(hist2, "DT AM w/ RPC", "l");
    // legend->AddEntry(hist2, str_stddev2.c_str(), "");
    // legend->SetTextSize(0.035); // Increase the text size in the legend
    // legend->Draw(); // Draw the legend

    // Create a legend
    TLegend *legend = new TLegend(0.13, 0.65, 0.35, 0.85); // Adjust the coordinates as needed
    legend->AddEntry(hist1,"DT AM", "l");
    legend->AddEntry(hist2, "DT AM w/ RPC", "l");
    legend->SetTextSize(0.035); // Increase the text size in the legend
    legend->Draw(); // Draw the legend

    canvas->SetGridy();
    if (logYflag) canvas->SetLogy();
    text->Draw();
    // if (norm) text2->Draw();

    canvas->Update(); // Update the canvas to display the histograms
    canvas->SaveAs(("histograms/twoHist/twoHist_"+str_name+".png").c_str()); // Save the canvas as an image 

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
    canvas->SaveAs(("histograms/twoHist/twoHist_"+str_name+".png").c_str()); // Save the canvas as an image
    canvas->SaveAs(("histograms/twoHist/twoHist_"+str_name+".pdf").c_str()); // Save the canvas as PDF

}

void plot_histograms(  TH1F *hist1, 
                        std::string str_name,
                        std::string str_Xaxis,
                        std::string str_leg = "",
                        bool norm=false,
                        bool logYflag=false) {

    if (!hist1 ) {
        std::cerr << "Error: Could not retrieve one or both histograms!" << std::endl;
        return;
    }

    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Histograms from Two Files", 800, 600);

    hist1->SetTitle("");

    // Set different colors for the histograms
    // hist1->SetLineColor(kRed);

    // Set Line Width
    hist1->SetLineWidth(3);

    // Set Line Width
    hist1->SetLineStyle(9);

    // Remove statistic box
    hist1->SetStats(0);
    
    // Get the standard deviation of each histogram
    double stddev1 = hist1->GetStdDev();
    stddev1 = std::round(stddev1*100)/100;
    std::string str_stddev1 = "#sigma = "+std::to_string(stddev1);

    // Normalize the histogram by its area
    if (norm){
        // Get the sum of bin contents
        double sum = hist1->Integral(1, hist1->GetNbinsX()); 
        if (sum != 0) {
            double scale = 1.0 / sum;
            hist1->Scale(scale);
        }  
    }

    hist1->Draw("HIST"); // Draw the second histogram on the same canvas

    TText *text = new TText(0.1,0.92,"CMS Preliminary");
    // text->SetNDC(); // To use the canvas coordinates
    // // text->SetTextAlign(31);
    // text->SetTextSize(0.06);
    // text->Draw();

    TLatex latex;
    latex.SetNDC(); // Use NDC (normalized device coordinates)
    // latex.SetTextAlign(22); // Centered alignment
    latex.SetTextSize(0.04); // Set text size
    latex.DrawLatex(0.1,0.92, "CMS #it{Phase-2 Simulation Preliminary}");  // (#it{...} makes the text italic)

    text = new TText(0.04,0.82,"Events"); // Events a.u.
    text->SetNDC();
    text->SetTextSize(0.06);
    text->SetTextAngle(90);
    if (norm) text->Draw();

    text = new TText(0.65,0.03, str_Xaxis.c_str());
    // text = new TText(0.50,0.03,"Segment timing [ns]"); str_Xaxis
    text->SetNDC();
    text->SetTextSize(0.05);
    text->Draw();

    text = new TText(0.75,0.85,"200 PU");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.05);
    if (norm) text->Draw();


    text = new TText(0.75,0.81,str_leg.c_str());
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.05);
    if (norm) text->Draw();

    // // // Create a legend
    TLegend *legend = new TLegend(0.13, 0.65, 0.35, 0.85); // Adjust the coordinates as needed
    legend->AddEntry(hist1,"DT AM", "l");
    legend->AddEntry(hist1, str_stddev1.c_str(), "");
    legend->SetTextSize(0.035); // Increase the text size in the legend
    legend->Draw(); // Draw the legend

    canvas->SetGridy();
    if (logYflag) canvas->SetLogy();
    text->Draw();
    // if (norm) text2->Draw();

    canvas->Update(); // Update the canvas to display the histograms
    // canvas->SaveAs(("histograms/twoHist/twoHist_"+str_name+".png").c_str()); // Save the canvas as an image
    canvas->SaveAs(("histograms/twoHist/twoHist_"+str_name+".pdf").c_str()); // Save the canvas as an PDF 

}

void eff_two_histograms_function(  TH1F *hist1, TH1F *hist2, 
                                    std::string str_name,
                                    std::string str_leg = "") {

    if (!hist1 || !hist2) {
        std::cerr << "Error: Could not retrieve one or both histograms!" << std::endl;
        return;
    }

    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Histograms from Two Files", 800, 600);

    hist1->SetTitle("");
    hist2->SetTitle("");

    // Set different colors for the histograms
    hist1->SetLineColor(kRed);
    hist2->SetLineColor(kBlue);

    // Remove statistic box
    hist1->SetStats(0);
    hist2->SetStats(0);

    // hist1->GetXaxis()->SetTitle("Gen #Eta");
    // hist2->GetXaxis()->SetTitle("Gen #Eta");

    // hist1-->SetYTitle("Gen #Eta");

    hist1->SetMarkerStyle(20);
    hist2->SetMarkerStyle(20);

    hist1->SetMarkerColor(kRed);
    hist2->SetMarkerColor(kBlue);

    hist2->Draw(""); // Draw the second histogram on the same canvas
    hist1->Draw("SAME");  // Draw the first histogram


    TText *text = new TText(0.1,0.92,"CMS Preliminary");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.06);
    text->Draw();

    text = new TText(0.75,0.85,"200 PU");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.05);
    text->Draw();
    
    double yValue = 0.9; // Define the y-value where you want to draw the horizontal line
    // Get the x-axis range
    double xMin = hist1->GetXaxis()->GetXmin();
    double xMax = hist1->GetXaxis()->GetXmax();
    // Create and draw the horizontal line
    TLine *line = new TLine(xMin, yValue, xMax, yValue);
    line->SetLineColor(kRed);
    line->SetLineWidth(2);
    line->SetLineStyle(2); // Dashed line
    line->Draw();

    // Create a legend
    TLegend *legend = new TLegend(0.76, 0.5, 0.96, 0.65); // Adjust the coordinates as needed
    legend->AddEntry(hist1,"DT AM", "p");
    legend->AddEntry(hist2, "DT AM w/ RPC", "p");
    legend->SetTextSize(0.03); // Increase the text size in the legend
    legend->Draw(); // Draw the legend

    canvas->SetGridy();
    canvas->Update(); // Update the canvas to display the histograms
    canvas->SaveAs(("histograms/twoHist_"+str_name+".png").c_str()); // Save the canvas as an image 

}

void plot_four_histograms_function( TH1F *hist1, TH1F *hist2,
                                    TH1F *hist3, TH1F *hist4,
                                    std::string str_name,
                                    std::string str_Xaxis,
                                    std::string str_leg = "",
                                    bool norm=false,
                                    bool logYflag=false) {

    if (!hist1 || !hist2 || !hist3 || !hist4) {
        std::cerr << "Error: Could not retrieve one or both histograms!" << std::endl;
        return;
    }

    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Histograms from Two Files", 800, 600);

    // Remove Title
    hist1->SetTitle("");
    hist2->SetTitle("");
    hist3->SetTitle("");
    hist4->SetTitle("");

    // Set different colors for the histograms
    // hist1->SetLineColor(kRed);
    // hist2->SetLineColor(kBlue);
    hist3->SetLineColor(kRed);
    hist4->SetLineColor(kBlue);

    // Set Line Width
    hist1->SetLineWidth(1);
    hist2->SetLineWidth(1);
    hist3->SetLineWidth(3);
    hist4->SetLineWidth(3);

    // Set Line Width
    // hist1->SetLineStyle(5);
    // hist2->SetLineStyle(5);
    hist3->SetLineStyle(9);
    hist4->SetLineStyle(1);

    // Remove statistic box
    hist1->SetStats(0);
    hist2->SetStats(0);
    hist3->SetStats(0);
    hist4->SetStats(0);

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

        sum = hist4->Integral(1, hist4->GetNbinsX()); 
        if (sum != 0) {
            double scale = 1.0 / sum;
            hist4->Scale(scale);
        }

 
    }

    // hist1->SetLineColor(kRed);
    hist1->SetFillColor(kRed);
    hist1->SetFillStyle(3006);

    // hist2->SetLineColor(kBlue); // Set colors of histograms
    hist2->SetFillColor(kBlue);
    hist2->SetFillStyle(3005); // Set fill style of histograms to transparent

    hist2->Draw("HIST"); // Draw the second histogram on the same canvas
    hist1->Draw("HIST SAME");  // Draw the first histogram
    hist3->Draw("HIST SAME");  // Draw the first histogram
    hist4->Draw("HIST SAME");  // Draw the first histogram

    TText *text = new TText(0.1,0.92,"CMS Preliminary");
    // text->SetNDC(); // To use the canvas coordinates
    // // text->SetTextAlign(31);
    // text->SetTextSize(0.06);
    // text->Draw();

    TLatex latex;
    latex.SetNDC(); // Use NDC (normalized device coordinates)
    // latex.SetTextAlign(22); // Centered alignment
    latex.SetTextSize(0.04); // Set text size
    latex.DrawLatex(0.1,0.92, "CMS #it{Phase-2 Simulation Preliminary}");  // (#it{...} makes the text italic)

    text = new TText(0.04,0.82,"a.u."); // Events
    text->SetNDC();
    text->SetTextSize(0.06);
    text->SetTextAngle(90);
    if (norm) text->Draw();

    // text = new TText(0.50,0.03,"Bunch Crossing Units [25ns]"); 
    text = new TText(0.50,0.03, str_Xaxis.c_str());
    text->SetNDC();
    text->SetTextSize(0.05);
    text->Draw();

    text = new TText(0.75,0.85,"200 PU");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.05);
    if (norm) text->Draw();

    text = new TText(0.75,0.81,str_leg.c_str());
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.05);
    if (norm) text->Draw();

    // // // Create a legend
    // TLegend *legend = new TLegend(0.13, 0.5, 0.35, 0.85); // Adjust the coordinates as needed
    // legend->AddEntry(hist1,"DT AM", "l");
    // legend->AddEntry(hist1, str_stddev1.c_str(), "");
    // legend->AddEntry(hist2, "DT AM w/ RPC", "l");
    // legend->AddEntry(hist2, str_stddev2.c_str(), "");
    // legend->SetTextSize(0.035); // Increase the text size in the legend
    // legend->Draw(); // Draw the legend

    // Create a legend
    TLegend *legend = new TLegend(0.13, 0.65, 0.35, 0.85); // Adjust the coordinates as needed
    legend->AddEntry(hist1,"DT AM", "f");
    legend->AddEntry(hist2, "DT AM w/ RPC", "f");
    legend->AddEntry(hist3, "DT AM", "l");
    legend->AddEntry(hist4, "DT AM w/ RPC", "l");
    legend->SetTextSize(0.035); // Increase the text size in the legend
    legend->Draw(); // Draw the legend

    canvas->SetGridy();
    if (logYflag) canvas->SetLogy();
    text->Draw();
    // if (norm) text2->Draw();

    canvas->Update(); // Update the canvas to display the histograms
    canvas->SaveAs(("histograms/fourHist/fourHist_"+str_name+".png").c_str()); // Save the canvas as an image 

}


void plot_two_histograms() {


    // Open the two ROOT files
    TFile *file1 = TFile::Open("output/DTDPGNtuple_histograms_noRPC.root");
    TFile *file2 = TFile::Open("output/DTDPGNtuple_histograms_withRPC.root");

    if (!file1 || !file2) {
        std::cout << "Error: Could not open one or both files!" << std::endl;
        return;
    }

    
    // ----------------------------------------------------------

    // ----------------------------------------------------------
    // ---- Time of the TPs (without matching) [BX]-----
    // ---------------------------------------------------------

    TH1F *hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1");
    TH1F *hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1", "Bunch Crossing Units [25ns]", "MB1 W-2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2", "Bunch Crossing Units [25ns]", "MB2 W-2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3", "Bunch Crossing Units [25ns]", "MB3 W-2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4", "Bunch Crossing Units [25ns]", "MB4 W-2", true);

    // ----------------------------------------------------------

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1", "Bunch Crossing Units [25ns]", "MB1 W-1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2", "Bunch Crossing Units [25ns]", "MB2 W-1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3", "Bunch Crossing Units [25ns]", "MB3 W-1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4", "Bunch Crossing Units [25ns]", "MB4 W-1", true);

    // ----------------------------------------------------------

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1", "Bunch Crossing Units [25ns]", "MB1 W0", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2", "Bunch Crossing Units [25ns]", "MB2 W0", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3", "Bunch Crossing Units [25ns]", "MB3 W0", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4", "Bunch Crossing Units [25ns]", "MB4 W0", true);

    // ----------------------------------------------------------

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1", "Bunch Crossing Units [25ns]", "MB1 W+1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2", "Bunch Crossing Units [25ns]", "MB2 W+1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3", "Bunch Crossing Units [25ns]", "MB3 W+1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4", "Bunch Crossing Units [25ns]", "MB4 W+1", true);

    // ----------------------------------------------------------

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1", "Bunch Crossing Units [25ns]", "MB1 W+2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2", "Bunch Crossing Units [25ns]", "MB2 W+2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3", "Bunch Crossing Units [25ns]", "MB3 W+2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4", "Bunch Crossing Units [25ns]", "MB4 W+2", true);

    // ----------------------------------------------------------
    // ---- Time of the TPs associated with prompt muons [BX]-----
    // ---------------------------------------------------------

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched", "Bunch Crossing Units [25ns]", "MB1 W-2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched", "Bunch Crossing Units [25ns]", "MB2 W-2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched", "Bunch Crossing Units [25ns]", "MB3 W-2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched", "Bunch Crossing Units [25ns]", "MB4 W-2", true);

    // ----------------------------------------------------------

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched", "Bunch Crossing Units [25ns]", "MB1 W-1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched", "Bunch Crossing Units [25ns]", "MB2 W-1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched", "Bunch Crossing Units [25ns]", "MB3 W-1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched", "Bunch Crossing Units [25ns]", "MB4 W-1", true);

    // ----------------------------------------------------------

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched", "Bunch Crossing Units [25ns]", "MB1 W0", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched", "Bunch Crossing Units [25ns]", "MB2 W0", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched", "Bunch Crossing Units [25ns]", "MB3 W0", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched", "Bunch Crossing Units [25ns]", "MB4 W0", true);

    // ----------------------------------------------------------

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched", "Bunch Crossing Units [25ns]", "MB1 W+1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched", "Bunch Crossing Units [25ns]", "MB2 W+1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched", "Bunch Crossing Units [25ns]", "MB3 W+1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched", "Bunch Crossing Units [25ns]", "MB4 W+1", true);

    // ----------------------------------------------------------

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched", "Bunch Crossing Units [25ns]", "MB1 W+2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched", "Bunch Crossing Units [25ns]", "MB2 W+2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched", "Bunch Crossing Units [25ns]", "MB3 W+2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched", "Bunch Crossing Units [25ns]", "MB4 W+2", true);


    // ----------------------------------------------------------
    // ----Time of the TPs associated with prompt muons [ns]-----
    // ----------------------------------------------------------
    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_1_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_1_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_1_matched", "Time of the TPs associated with prompt muons [ns]", "MB1 W-2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_2_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_2_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_2_matched", "Time of the TPs associated with prompt muons [ns]", "MB2 W-2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_3_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_3_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_3_matched", "Time of the TPs associated with prompt muons [ns]", "MB3 W-2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_4_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_4_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_m2_station_4_matched", "Time of the TPs associated with prompt muons [ns]", "MB4 W-2", true);

    // ----------------------------------------------------------

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_1_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_1_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_1_matched", "Time of the TPs associated with prompt muons [ns]", "MB1 W-1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_2_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_2_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_2_matched", "Time of the TPs associated with prompt muons [ns]", "MB2 W-1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_3_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_3_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_3_matched", "Time of the TPs associated with prompt muons [ns]", "MB3 W-1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_4_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_4_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_m1_station_4_matched", "Time of the TPs associated with prompt muons [ns]", "MB4 W-1", true);

    // ----------------------------------------------------------

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_1_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_1_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_1_matched", "Time of the TPs associated with prompt muons [ns]", "MB1 W0", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_2_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_2_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_2_matched", "Time of the TPs associated with prompt muons [ns]", "MB2 W0", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_3_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_3_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_3_matched", "Time of the TPs associated with prompt muons [ns]", "MB3 W0", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_4_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_4_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_0_station_4_matched", "Time of the TPs associated with prompt muons [ns]", "MB4 W0", true);

    // ----------------------------------------------------------

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_1_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_1_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_1_matched", "Time of the TPs associated with prompt muons [ns]", "MB1 W+1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_2_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_2_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_2_matched", "Time of the TPs associated with prompt muons [ns]", "MB2 W+1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_3_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_3_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_3_matched", "Time of the TPs associated with prompt muons [ns]", "MB3 W+1", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_4_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_4_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_p1_station_4_matched", "Time of the TPs associated with prompt muons [ns]", "MB4 W+1", true);

    // ----------------------------------------------------------

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_1_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_1_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_1_matched", "Time of the TPs associated with prompt muons [ns]", "MB1 W+2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_2_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_2_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_2_matched", "Time of the TPs associated with prompt muons [ns]", "MB2 W+2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_3_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_3_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_3_matched", "Time of the TPs associated with prompt muons [ns]", "MB3 W+2", true);

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_4_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_4_matched");
    plot_two_histograms_function2( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_wheel_p2_station_4_matched", "Time of the TPs associated with prompt muons [ns]", "MB4 W+2", true);








    hist1 = (TH1F*)file1->Get("histogram_ph2Tseg_phi_t0_Genmatched");
    hist2 = (TH1F*)file2->Get("histogram_ph2Tseg_phi_t0_Genmatched");
    plot_histograms( hist1, "histogram_ph2Tseg_phi_t0_Genmatched", "Segment timing [ns]", " ", false);

    // ----------------------------------------------------------


    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_t0_matched");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_t0_matched");
    plot_two_histograms_function( hist1, hist2, "histogram_ph2TpgPhiEmuAm_t0_matched", "TDCs"," ", true);



    TH1F *hist3 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1");
    TH1F *hist4 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1");

    hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1");
    hist2 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1");
    hist3 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched");
    hist4 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched");
    plot_four_histograms_function( hist1, hist2, hist3, hist4,
                                    "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1", 
                                     "Bunch Crossing Units [25ns]", "MB1 W0", true, false);




   


            



    // Clean up
    delete file1;
    delete file2;

    std::cout << "--------------------------------" << std::endl;
    std::cout << "END PROGRAM" << std::endl;
    std::cout << "--------------------------------" << std::endl;

}

