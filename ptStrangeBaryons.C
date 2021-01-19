#include <iostream> 
#include "TH1.h"
#include "TLorentzVector.h"
#include "TGraph.h"
#include "TString.h" 
using namespace std;

	
void ptStrangeBaryons(){

   
	Float_t dy = 0.5;//rapidity range
	Float_t dy1 = 1;
	Float_t dy2 = 0.75;

	Int_t Nevents = 0;
	Float_t rapidity;
	Int_t id,nevent,nrun,mult,NpartP,NpartT,NELP,NINP,NELT,NINT;
	Float_t px,py,pz,m,x,y,z,t,impactpar,passhead;
	Float_t pt;

	TH1F *h_pion=new TH1F("pion+","pion+",40,0.0,2.0);
	TH1F *h_antiPion=new TH1F("pion-","pion-",40,0.0,2.0);
	TH1F *h_kaon=new TH1F("kaon","",40,0.0,2.0);
	TH1F *h_antiKaon=new TH1F("antiKaon","anti-kaon",40,0.0,2.0);
	TH1F *h_proton=new TH1F("proton","proton",40,0.0,2.0);
	TH1F *h_antiProton=new TH1F("antiProton","proton",40,0.0,2.0);
	TH1F *h_pbar=new TH1F("pbar","pbar",40,0.0,2.0);
  
	
	for(int file=0;file<100;file++){
	    
        TString myfile = "afterART_";
        myfile +=file;
        myfile +=".dat";

        ifstream filein;
    	filein.open(myfile);
	        
    	if(!filein){
		printf("can not open the data file");
		return 1;
    	}
	
		while(filein >> nevent){	
			filein  >> nrun >> mult >> impactpar >> NpartP >> NpartT >> NELP >> NINP >> NELT >> NINT >> passhead;
		
			Nevents++;		

      		for(Int_t i=0;i<mult;i++){
			
				filein >> id >> px >> py >> pz >> m >> x >> y >> z >> t;	

				if(id!=211&&id!=-211&&id!=321&&id!=-321&&id!=2212&&id!=-2212) continue;
				TLorentzVector particle;
				particle.SetXYZM(px,py,pz,m);
				pt= particle.Perp();
                if(pt<1e-4) continue;
				rapidity = particle.Rapidity();

				if(fabs(rapidity)<dy){
                if(id==3122) { h_lambda->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//Lambda
                if(id==-3122){ h_antiLambda->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//antiLambda
                if(id==3312) { h_xi->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//Xi minus       	
                if(id==-3312){ h_antiXi->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//antiXi minus
                if(id==3334||id==-3334) { h_omega->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//Omega minus			
                    
				}
			
			
			}

		
		}
	cout << "read in  #events: " <<Nevents<<endl; 	
	filein.close();
    
	}
	TCanvas *c1 = new TCanvas();
	c1->SetLogy(1);

//Lambda
	h_lambda->Scale(1.0/Nevents);
	h_lambda->SetMarkerStyle(107);
   	h_lambda->SetLineColor(2);
	h_lambda->Draw("e");
    h_lambda->GetXaxis()->SetTitle("p_{T}(GeV/c)");
	h_lambda->GetYaxis()->SetTitle("#frac{1}{2#pip_{T}}#frac{dN^{2}}{dydp_{T}}[(GeV/c)_{-2}]");
	TGraph *gr_lambda = new TGraph("lambda200-pt.txt");
	gr_lambda->SetLineColor(7);
    gr_lambda->Draw("same");

//antiLambda
	h_antiLambda->Scale(1.0/Nevents);
	h_antiLambda->SetMarkerStyle(8);
   	h_antiLambda->SetLineColor(4);
	h_antiLambda->Draw("same");
	TGraph *gr_antiLambda = new TGraph("antiLambda200-pt.txt");
	gr_antiLambda->SetLineColor(4);
    gr_lambda->Draw("same");

//Xi
	h_xi->Scale(1.0/Nevents);
	h_xi->SetMarkerStyle(46);
   	h_xi->SetLineColor(9);
	h_xi->Draw("same");
	TGraph *gr_xi = new TGraph("xi200-pt.txt");
	gr_xi->SetLineColor(9);
    gr_xi->Draw("same");

//anti-Xi
	h_antiXi->Scale(1.0/Nevents);
	h_antiXi->SetMarkerStyle(47);
   	h_antiXi->SetLineColor(4);
	h_antiXi->Draw("same");
	TGraph *gr_antiXi = new TGraph("antiXi200-pt.txt");
	gr_antiXi->SetLineColor(4);
    gr_antiXi->Draw("same");

//Omega
	h_omega->Scale(1.0/Nevents);
	h_omega->SetMarkerStyle(29);
   	h_omega->SetLineColor(2);
	h_omega->Draw("same");
	TGraph *gr_omega = new TGraph("omega+antiOmega.txt");
	gr_omega->SetLineColor(2);
 	gr_omega->Draw("same");


    TLegend *legend1 = new TLegend();
	legend1->AddEntry(h_lambda,"#Lambda");
	legend1->AddEntry(gr_lambda,"Exp 0-5%");
	legend1->AddEntry(h_antiLambda,"#bar{#Lambda}");
	legend1->AddEntry(gr_antiLambda,"Exp 0-5%");
	
	legend1->AddEntry(h_xi,"#Xi^{-}");
	legend1->AddEntry(gr_xi,"Exp 0-5%");
	legend1->AddEntry(h_antiXi,"#bar{#Xi}^{+}");
	legend1->AddEntry(gr_antiXi,"Exp 0-5%");
	
	legend1->AddEntry(h_omega,"#Omega^{+}+#Omega^{-}");
	legend1->AddEntry(gr_omega,"Exp 0-5%");

	legend1->Draw();
	    
	
	

	    
    c1->SaveAs("pi-k-proton-pt.pdf");

}
