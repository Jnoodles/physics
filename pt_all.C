#include <iostream> 
#include "TH1.h"
#include "TLorentzVector.h"
#include "TGraph.h"
#include "TString.h" 
using namespace std;

	
void pt_strange(){

  
	Float_t dy = 0.5;//rapidity range
//	Float_t dy1 = 1;
//	Float_t dy2 = 0.75;

	Int_t Nevents = 0;
	Float_t rapidity;
	Int_t id,nevent,nrun,mult,NpartP,NpartT,NELP,NINP,NELT,NINT;
	Float_t px,py,pz,m,x,y,z,t,impactpar,passhead;
	Float_t pt;

	TH1F *h_pion=new TH1F("pion+","",40,0.0,2.0);
	TH1F *h_antiPion=new TH1F("pion-","pion-",40,0.0,2.0);
	TH1F *h_kaon=new TH1F("kaon","",40,0.0,2.0);
	TH1F *h_antiKaon=new TH1F("antiKaon","anti-kaon",40,0.0,2.0);
	TH1F *h_proton=new TH1F("proton","proton",40,0.0,2.0);
	TH1F *h_antiProton=new TH1F("antiProton","proton",40,0.0,2.0);
	TH1F *h_pbar=new TH1F("pbar","pbar",40,0.0,2.0);
   	TH1F *h_lambda=new TH1F("lambda","lambda",40,0.0,2.0);
	TH1F *h_antiLambda = new TH1F("antiLambda","anti-lambda",40,0.0,2.0);
	TH1F *h_xi = new TH1F("xi","xi",40,0.0,2.0);
	TH1F *h_antiXi = new TH1F("antiXi","anti-xi",40,0.0,2.0);
	TH1F *h_omega = new TH1F("Omega","Omega",40,0.0,2.0);
	//TH1F *h_antiOmega = new TH1F("antOmega","anti-Omega",40,0.0,2.0);
	
	
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
					if(id!=211&&id!=-211&&id!=321&&id!=-321&&id!=2212&&id!=-2212&&id!=3122&&id!=-3122&&id!=3312&&id!=-3312&&id!=3334&&id!=-3334) continue;
					TLorentzVector particle;
					particle.SetXYZM(px,py,pz,m);
					pt= particle.Perp();
					if(pt<1e-4) continue;

					rapidity = particle.Rapidity();
					if(fabs(rapidity)>dy)	continue;

					if(id==211)  { h_pion->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); } //pion+
					if(id==-211) { h_antiPion->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); } //pion-
					if(id==321)  { h_kaon->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//kaon+
					if(id==-321) { h_antiKaon->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//kaon-
					if(id==2212) { h_proton->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//proton
					if(id==-2212){ h_antiProton->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//anti-proton					
					if(id==3122) { h_lambda->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//Lambda
					if(id==-3122){ h_antiLambda->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//antiLambda
					if(id==3312) { h_xi->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//Xi minus       	
					if(id==-3312){ h_antiXi->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//antiXi minus
					if(id==3334||id==-3334) { h_omega->Fill(pt,0.5/(3.14159*pt*2*dy*0.05)); }	//Omega minus
		
				
				
				}

				
			}
			cout << "read in  #events: " <<Nevents<<endl; 	
			filein.close();
			
	}
	
	
	TCanvas *c1 = new TCanvas();
	c1->SetLogy(1);
	gStyle->SetOptStat(0);

//pion+
	h_pion->Scale(1.0/Nevents);
	h_pion->SetMarkerStyle(20);
    h_pion->SetLineColor(kRed);
	h_pion->GetXaxis()->SetTitle("p_{T}(GeV/c)");
	h_pion->GetYaxis()->SetTitle("#frac{1}{2#pip_{T}}#frac{dN^{2}}{dydp_{T}}[(GeV/c)^{-2}]");
	h_pion->Draw("e");
	TGraph *gr_pion = new TGraph("pion200-pt.txt");
	gr_pion->SetLineColor(kRed);
    gr_pion->Draw("same");

//pion-
	h_antiPion->Scale(1.0/Nevents);
	h_antiPion->SetMarkerStyle(24);
   	h_antiPion->SetLineColor(kBlue);
	h_antiPion->Draw("same");
	TGraph *gr_antiPion = new TGraph("antiPion200-pt.txt");
	gr_antiPion->SetLineColor(kBlue);
    gr_antiPion->Draw("same");
//kaon+
	h_kaon->Scale(1.0/Nevents);
	h_kaon->SetMarkerStyle(37);
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
	h_proton->SetMarkerStyle(26);
    h_proton->SetLineColor(kBlack);
	h_proton->Draw("same");
	TGraph *gr_proton = new TGraph("proton200-pt.txt");
	gr_proton->SetLineColor(kBlack);
    gr_proton->Draw("kYellow");

//antiProton
	h_antiProton->Scale(1.0/Nevents);
	h_antiProton->SetMarkerStyle(25);
    h_antiProton->SetLineColor(kYellow);
	h_antiProton->Draw("same");
	TGraph *gr_antiProton = new TGraph("antiProton200-pt.txt");
	gr_antiProton->SetLineColor(kYellow);
    gr_antiProton->Draw("same");

//Lambda
	h_lambda->Scale(1.0/Nevents);
	h_lambda->SetMarkerStyle(44);
   	h_lambda->SetLineColor(2);
	h_lambda->Draw("same");
	TGraph *gr_lambda = new TGraph("lambda200-pt.txt");
	gr_lambda->SetLineColor(2);
    gr_lambda->Draw("same");

//antiLambda
	h_antiLambda->Scale(1.0/Nevents);
	h_antiLambda->SetMarkerStyle(45);
   	h_antiLambda->SetLineColor(kGreen);
	h_antiLambda->Draw("same");
	TGraph *gr_antiLambda = new TGraph("antiLambda200-pt.txt");
	gr_antiLambda->SetLineColor(kGreen);
    gr_antiLambda->Draw("same");

//Xi
	h_xi->Scale(1.0/Nevents);
	h_xi->SetMarkerStyle(46);
   	h_xi->SetLineColor(kViolet);
	h_xi->Draw("same");
	TGraph *gr_xi = new TGraph("xi200-pt.txt");
	gr_xi->SetLineColor(kViolet);
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
	h_omega->SetMarkerStyle(38);
   	h_omega->SetLineColor(2);
	h_omega->Draw("same");
	TGraph *gr_omega = new TGraph("omega+antiOmega.txt");
	gr_omega->SetLineColor(2);
 	gr_omega->Draw("same");

     
		

	

	
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
	    
    //c1->SaveAs("strangeness-pt.pdf");

}
