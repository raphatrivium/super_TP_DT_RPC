#include <iostream>
#include <string>
#include <typeinfo> // see the type of a variable
#include <fstream> // create and write file
#include <vector>
#include <filesystem>
#include <cmath>
#include <unordered_map>
#include <set>

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


std::map<std::string, TH1*> m_plots;

void printProgress(double percentage) {
    int barWidth = 70; // Width of the progress bar

    std::cout << "[";
    int pos = barWidth * percentage;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(percentage * 100.0) << " %\r";
    std::cout.flush();
}

double deltaPhifunction( double phi1, double phi2) {

    double deltaPhi = phi1 - phi2;
    if  (deltaPhi > M_PI)
        deltaPhi -= 2.0*M_PI;
    if (deltaPhi <= -M_PI)
        deltaPhi += 2.0*M_PI;

    return deltaPhi;
}

double deltaRfunction(double eta1, double phi1, double eta2, double phi2) {
    // Caclulation of Delta R between generated particle and reconstructed particle
    double deltaEta = eta1 - eta2;
    double deltaPhi = phi1 - phi2;
    if  (deltaPhi > M_PI)
        deltaPhi -= 2.0*M_PI;
    if (deltaPhi <= -M_PI)
        deltaPhi += 2.0*M_PI;

    double deltaR = std::sqrt(deltaEta * deltaEta + deltaPhi * deltaPhi);

    // if (deltaR > M_PI) deltaR = deltaR - M_PI;

    return deltaR;
}