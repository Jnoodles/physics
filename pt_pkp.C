#include <iostream> 
#include "TH1.h"
#include "TLorentzVector.h"
#include "TGraph.h"
#include "TString.h" 
using namespace std;

	
void pt_pkp(){

   
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
				rapidity = particle.Rapidity();

				if(pt<1e-4) continue;

				if(fabs(rapidity)<dy){
				if(id==211)  { h_pion->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); } //pion+
				if(id==-211) { h_antiPion->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); } //pion-
				if(id==321)  { h_kaon->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//kaon+
				if(id==-321) { h_antiKaon->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//kaon-
				if(id==2212) { h_proton->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//proton
				if(id==-2212){ h_pbar->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//anti-proton					
				
				}
			
			
			}

		
		}
	cout << "read in  #events: " <<Nevents<<endl; 	
	filein.close();
    
	}
	TCanvas *c1 = new TCanvas();
	c1->SetLogy(1);

//pion+
	h_pion->Scale(1.0/Nevents);
	h_pion->SetMarkerStyle(20);
    h_pion->SetLineColor(kRed);
    h_pion->GetXaxis()->SetTitle("p_{T}(GeV/c)");
	h_pion->GetYaxis()->SetTitle("#frac{1}{2#pip_{T}}#frac{dN^{2}}{dydp_{T}}[(GeV/c)_{-2}]");
	h_pion->Draw("e");
	TGraph *gr_pion = new TGraph("proton200-pt.txt");
	gr_pion->SetLineColor(kRed);
    gr_pion->Draw("same");

//pion-
	h_antiPion->Scale(1.0/Nevents);
	h_antiPion->SetMarkerStyle(24);
   	h_pion->SetLineColor(kBlue);
	h_antiPion->Draw("same");
	TGraph *gr_antiPion = new TGraph("antiPion200-pt.txt");
	gr_antiPion->SetLineColor(kBlue);
    gr_antiPion->Draw("same");
//kaon+
	h_kaon->Scale(1.0/Nevents);
	h_kaon->SetMarkerStyle(39);
    h_kaon->SetLineColor(4);
	h_kaon->Draw("same");
	TGraph *gr_kaon = new TGraph("kaon200-pt.txt");
	gr_kaon->SetLineColor(4);
    gr_kaon->Draw("same");
//kaon-
	h_antiKaon->Scale(1.0/Nevents);
	h_antiKaon->SetMarkerStyle(39);
    h_antiKaon->SetLineColor(6);
	h_antiKaon->Draw("same");
	TGraph *gr_antiKaon = new TGraph("antiKaon200-pt.txt");
	gr_antiKaon->SetLineColor(6);
    gr_antiKaon->Draw("same");

//proton
	h_proton->Scale(1.0/Nevents);
	h_proton->SetMarkerStyle(27);
    h_proton->SetLineColor(2);
	h_proton->Draw("same");
	TGraph *gr_proton = new TGraph("proton200-pt.txt");
	gr_proton->SetLineColor(2);
    gr_proton->Draw("same");

//antiProton
	h_antiProton->Scale(1.0/Nevents);
	h_antiProton->SetMarkerStyle(33);
    h_antiProton->SetLineColor(6);
	h_antiProton->Draw("same");
	TGraph *gr_antiProton = new TGraph("antiProton200-pt.txt");
	gr_antiProton->SetLineColor(6);
    gr_antiProton->Draw("same");


	
	TLegend *legend = new TLegend();
	legend->AddEntry(h_pion,"#pi^{+}");
	legend->AddEntry(gr_pion,"Exp 0-5%");
	legend->AddEntry(h_antiPion,"#pi^{-}");
	legend->AddEntry(gr_antiPion,"Exp 0-5%");
	
	legend->AddEntry(h_kaon,"k^{+}");
	legend->AddEntry(gr_kaon,"Exp 0-5%");
	legend->AddEntry(h_antiKaon,"k^{-}");
	legend->AddEntry(gr_antiKaon,"Exp 0-5%");
	
	legend->AddEntry(h_proton,"p");
	legend->AddEntry(gr_proton,"Exp 0-5%");
	legend->AddEntry(h_antiProton,"#bar{p}");
	legend->AddEntry(gr_antiProton,"Exp 0-5%");
	
	
	legend->Draw();
	    
    c1->SaveAs("pi-k-proton-pt.pdf");

}
