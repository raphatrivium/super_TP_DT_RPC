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
#include <TMarker.h>
#include <TLine.h>
#include <TPaveText.h>
#include <TLatex.h>

#include <iostream>
#include <string>
#include <typeinfo> // see the type of a variable
#include <fstream> // create and write file
#include <vector>
#include <filesystem>
#include <cmath>
#include <unordered_map>

double get_standard_deviation(  TH1F *hist) {

    double stddev = 0.;

    if (!hist) {
        std::cerr << "Error: Could not retrieve one or both histograms!" << std::endl;
        return stddev = 0.;
    }
    // Get the standard deviation of each histogram
    stddev = hist->GetStdDev();

    return stddev;
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

void plot_eff(){


    // Open the two ROOT files
    TFile *file1 = TFile::Open("output/DTDPGNtuple_histograms_noRPC.root");
    TFile *file2 = TFile::Open("output/DTDPGNtuple_histograms_withRPC.root");

    if (!file1 || !file2) {
        std::cout << "Error: Could not open one or both files!" << std::endl;
        return;
    }

    double totalEntries = 0.;
    double totalEntries2 = 0.;
    double effi = 0.;

    string str_hist = "";


    

    TH1F *hist1 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1");
    TH1F *hist2 = (TH1F*)file1->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1");
    TH1F *hist3 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1");
    TH1F *hist4 = (TH1F*)file2->Get("histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1");


    std::vector<double> vec_values1;
    std::vector<double> vec_values2;

    // "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched_numerator"


    std::vector<std::string> file_names = { "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_1_matched", 
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_1_matched",
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_1_matched",
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_1_matched",
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_1_matched",

                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_2_matched", 
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_2_matched",
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_2_matched",
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_2_matched",
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_2_matched",

                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_3_matched", 
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_3_matched",
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_3_matched",
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_3_matched",
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_3_matched",

                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_m2_station_4_matched", 
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_m1_station_4_matched",
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_0_station_4_matched",
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_p1_station_4_matched",
                                            "histogram_ph2TpgPhiEmuAm_BX_wheel_p2_station_4_matched"
                                                };

    for (size_t i = 0; i < file_names.size(); ++i) {

        hist1 = (TH1F*)file1->Get(file_names[i].c_str());
        hist2 = (TH1F*)file1->Get((file_names[i]+"_numerator").c_str());
        totalEntries = hist1->GetEntries();
        totalEntries2 = hist2->GetEntries();
        effi = totalEntries2/totalEntries;
        vec_values1.push_back(effi);

        hist3 = (TH1F*)file2->Get(file_names[i].c_str());
        hist4 = (TH1F*)file2->Get((file_names[i]+"_numerator").c_str());
        totalEntries = hist3->GetEntries();
        totalEntries2 = hist4->GetEntries();
        effi = totalEntries2/totalEntries;  
        vec_values2.push_back(effi);

    }


    std::cout << "----------------------------------------" << std::endl;
    std::cout << "vec_values1 [" << std::endl;
    for (size_t k = 0; k < vec_values1.size(); ++k) {
        std::cout << vec_values1[k] << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "vec_values2 [" << std::endl;
    for (size_t k = 0; k < vec_values2.size(); ++k) {
        std::cout << vec_values2[k] << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;


    // Create a TH2F histogram
    TH2F *histogram_std_noRPC = new TH2F("histogram_std_noRPC", "Wheels; Wheels ; Efficiency", 21, 0, 21, 100, 0, 1.1);
    TH2F *histogram_std_withRPC = new TH2F("histogram_std_withRPC", "Wheels; Wheels ; Efficiency", 21, 0, 21, 100, 0, 1.1);

    histogram_std_noRPC->SetTitle("   ;   ; ");
    histogram_std_withRPC->SetTitle(" ;   ; ");

    histogram_std_noRPC->GetYaxis()->SetTitle("Efficiency");
    histogram_std_withRPC->GetYaxis()->SetTitle("Efficiency");

    histogram_std_noRPC->GetYaxis()->SetTitleSize(0.07);  // Adjust the size value as needed
    histogram_std_withRPC->GetYaxis()->SetTitleSize(0.07);  // Adjust the size value as needed

    histogram_std_noRPC->GetYaxis()->SetTitleOffset(0.5); // Offset of the labels from the axis
    histogram_std_withRPC->GetYaxis()->SetTitleOffset(0.5); // Offset of the labels from the axis


    std::cout << "vec_values1.size(): " << vec_values1.size() << std::endl;
    std::cout << "vec_values2.size(): " << vec_values2.size() << std::endl;

    for (size_t i = 0; i < vec_values1.size(); ++i) {

        // histogram_std_noRPC->Fill(i, vec_values1[i]);

        // histogram_std_withRPC->Fill(i, vec_values2[i]);

        // std::cout << "bin: " << i+1 << std::endl;

    }


    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Histograms from Two Files", 800, 600);


    histogram_std_noRPC->SetMarkerStyle(20);
    histogram_std_withRPC->SetMarkerStyle(20);

    histogram_std_noRPC->SetMarkerColor(kRed);
    histogram_std_withRPC->SetMarkerColor(kBlue);

    histogram_std_noRPC->SetStats(0);
    histogram_std_withRPC->SetStats(0);

    histogram_std_noRPC->SetTitle(" ");
    histogram_std_withRPC->SetTitle(" ");



    // histogram_std_noRPC->GetXaxis()->SetLabelOffset(0.02); // Offset of the labels from the axis
    // histogram_std_withRPC->GetXaxis()->SetLabelOffset(0.02); // Offset of the labels from the axis

    histogram_std_noRPC->GetXaxis()->SetLabelSize(0.05);  // Set the X-axis label size
    histogram_std_withRPC->GetXaxis()->SetLabelSize(0.06);  // Set the X-axis label size

    histogram_std_withRPC->Draw(); // Draw the legend
    histogram_std_noRPC->Draw("SAME"); // Draw the legend

    // Define the custom labels for the X-axis
    TString xLabels[] = {"-2", "-1", "0", "+1", "+2", "-2", "-1", "0", "+1", "+2", "-2", "-1", "0", "+1", "+2", "-2", "-1", "0", "+1", "+2"};
    // Assign labels to X-axis bins
    for (int i = 1; i <= 20; ++i) {
        histogram_std_noRPC->GetXaxis()->SetBinLabel(i, xLabels[i-1]);
        histogram_std_withRPC->GetXaxis()->SetBinLabel(i, xLabels[i-1]);
    }
    
    // Define the x value where you want to draw the vertical line
    double xValue = 6.;
    // Get the y-axis range of the histogram
    double yMin = histogram_std_withRPC->GetMinimum();
    double yMax = histogram_std_withRPC->GetMaximum();
    // Create a vertical line at the specified x value
    TLine *line = new TLine(xValue, yMin, xValue, yMax);
    line->SetLineColor(kBlack); // Set line color
    line->SetLineWidth(3); // Set line width
    line->SetLineStyle(1); // Set line style (2 = dashed line)
    line->Draw(); // Draw the line on the same canvas

    for (size_t i = 0; i < vec_values1.size(); ++i) {

        double xValue = i+1;
        double yValue = vec_values1[i];

        TMarker *marker = new TMarker(xValue, yValue, kFullCircle);
        marker->SetMarkerColor(kRed);  // Set the marker color
        marker->SetMarkerSize(1.5);    // Set the marker size
        marker->Draw();                // Draw the marker on the canvas
    }

    for (size_t i = 0; i < vec_values2.size(); ++i) {

        double xValue = i+1;
        double yValue = vec_values2[i];

        TMarker *marker = new TMarker(xValue, yValue, kFullCircle);
        marker->SetMarkerColor(kBlue);  // Set the marker color
        marker->SetMarkerSize(1.5);    // Set the marker size
        marker->Draw();                // Draw the marker on the canvas
    }



    TText *text = new TText(0.1,0.92,"CMS #it{Phase-2 Simulation Preliminary}");
    // text->SetNDC(); // To use the canvas coordinates
    // // text->SetTextAlign(31);
    // text->SetTextSize(0.06);
    // text->Draw();

    TLatex latex;
    latex.SetNDC(); // Use NDC (normalized device coordinates)
    // latex.SetTextAlign(22); // Centered alignment
    latex.SetTextSize(0.04); // Set text size
    latex.DrawLatex(0.1,0.92, "CMS #it{Phase-2 Simulation Preliminary}");  // (#it{...} makes the text italic)

    text = new TText(0.75,0.85,"200 PU");
    text->SetNDC(); // To use the canvas coordinates
    // text->SetTextAlign(31);
    text->SetTextSize(0.05);
    text->Draw();

    text = new TText(0.80,0.01,"Wheels");
    text->SetNDC();
    text->SetTextSize(0.05);
    text->Draw();
    

    // canvas->SetGridy();
    canvas->SetGridx();

    

    // Create a TPaveText object
    double txt_x1 = 0.15;
    double txt_x2 = 0.25;

    double txt_y1 =  0.2;
    double txt_y2 = 0.25;

    TPaveText *paveText = new TPaveText(txt_x1, txt_y1, txt_x2,txt_y2, "NDC"); // (x1, y1, x2, y2, "NDC")
    paveText->SetFillColor(kWhite); // Set the background color to white
    // Set the border size (optional)
    paveText->SetBorderSize(2); // Border width, 0 means no border
    paveText->AddText("MB1");
    paveText->Draw();

    paveText = new TPaveText(0.34, 0.2, 0.44,0.25, "NDC"); // (x1, y1, x2, y2, "NDC")
    paveText->SetFillColor(kWhite); // Set the background color to white
    // Set the border size (optional)
    paveText->SetBorderSize(2); // Border width, 0 means no border
    paveText->AddText("MB2");
    paveText->Draw();

    paveText = new TPaveText(0.53, 0.2, 0.63, 0.25, "NDC"); // (x1, y1, x2, y2, "NDC")
    paveText->SetFillColor(kWhite); // Set the background color to white
    // Set the border size (optional)
    paveText->SetBorderSize(2); // Border width, 0 means no border
    paveText->AddText("MB3");
    paveText->Draw();

    paveText = new TPaveText(0.72, 0.2, 0.82,0.25, "NDC"); // (x1, y1, x2, y2, "NDC")
    paveText->SetFillColor(kWhite); // Set the background color to white
    // Set the border size (optional)
    paveText->SetBorderSize(2); // Border width, 0 means no border
    paveText->AddText("MB4");
    paveText->Draw();

    // paveText = new TPaveText( txt_x1, txt_y1, txt_x2,txt_y2, "NDC"); // (x1, y1, x2, y2, "NDC")
    // paveText->SetFillColor(kWhite); // Set the background color to white
    // // Set the border size (optional)
    // paveText->SetBorderSize(2); // Border width, 0 means no border
    // paveText->AddText("MB2");
    // paveText->Draw();

    // text = new TText(0.15,0.2,"MB1");
    // text->SetNDC(); // To use the canvas coordinates
    // // text->SetTextAlign(31);
    // text->SetFillColor(kWhite);
    // text->SetTextSize(0.05);
    // text->Draw();


    canvas->Update(); // Update the canvas to display the histograms
    canvas->SaveAs("histograms/eff.png"); // Save the canvas as an image





    std::cout << "--------------------------------" << std::endl;
    std::cout << "END PROGRAM" << std::endl;
    std::cout << "--------------------------------" << std::endl;





}