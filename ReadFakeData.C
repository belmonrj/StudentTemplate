void ReadFakeData()
{


  // it's possible to work around this, but generally it's easiest and simplest
  // when we know before hand how much data we're reading in
  const int nbins = 10;
  double x[nbins]; // x-coordinate
  double y[nbins]; // y-coordinate
  double ex[nbins]; // uncertainty on x
  double ey[nbins]; // uncertainty on y

  // setup the file to be read in
  ifstream fin("data.txt");
  // make a for loop to read in the data
  for ( int i = 0; i < nbins; ++i )
    {
      fin >> x[i] >> y[i] >> ey[i];
      ex[i] = 0; // usually, but not always, the uncertainty on x is taken to be zero
    }
  // close the file
  fin.close();

  // this is a ROOT object used for drawing data
  // here we create it and set its basic properties
  TGraphErrors* tge = new TGraphErrors(nbins,x,y,ex,ey);
  tge->SetMarkerColor(kBlack);
  tge->SetMarkerStyle(kOpenSquare);

  // now we do some setup to do the drawing
  // there's a variety of ways to do this
  // but this one works well and is flexible

  // a TCanvas is always needed
  // everything is drawn on a canvas
  TCanvas* c1 = new TCanvas("c1","");

  // pick the end points for the axes
  // these are picked based on the range of data in the text file
  double xmin = 0.0;
  double xmax = 1.1;
  double ymin = 0.0;
  double ymax = 15.0;

  // i like to draw a dummy histogram
  // it's easy and convenient to draw various objects on top as needed
  TH2D* hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->GetXaxis()->SetTitle("x"); // label for x-axis
  hdummy->GetYaxis()->SetTitle("y"); // label for y-axis
  hdummy->Draw(); // draw the dummy histogram as a frame
  tge->Draw("p"); // draw the TGraphErrors on top

  // now that we've drawn the data, let's do a fit
  // we start by defining a function
  TF1* fun = new TF1("fun","[0]+[1]*x",xmin,xmax);

  // now we fit the TGraphErrors
  // there are many different ways to do this
  // this is just one possibility
  tge->Fit("fun","R"); // name of funtion, option R means use range specified in the constructor

  // now we'll make a legend to show what's on the plot
  TLegend* leg = new TLegend(0.18,0.72,0.38,0.92); // position on canvas range 0-1: xlow, ylow, xhigh, yhigh
  leg->AddEntry(tge,"data","p"); // pointer to object, string to display, option for symbol p = point
  leg->AddEntry(fun,"fit","l"); // pointer to object, string to display, option for symbol l = line
  leg->Draw();

  // now we'll draw some information from the fit onto the plot
  // there's an easier way but this way is much more flexible
  double p0 = fun->GetParameter(0);
  double ep0 = fun->GetParError(0);
  double p1 = fun->GetParameter(1);
  double ep1 = fun->GetParError(1);
  double chi2 = fun->GetChisquare();
  int ndf = fun->GetNDF();
  TLatex* tex = new TLatex(0.6,0.30,Form("#chi^{2}/NDF = %.2f / %d",chi2,ndf));
  tex->SetNDC();
  tex->Draw();
  tex->DrawLatex(0.6,0.25,Form("p0 = %.2f #pm %.2f",p0,ep0));
  tex->DrawLatex(0.6,0.20,Form("p1 = %.2f #pm %.2f",p1,ep1));

  // once everything is drawn on the canvas, print it to file
  c1->Print("test_figure.png");

  // now that we're all done, free up all the allocated memory
  // for a single use function this isn't necessary
  // but it's good to have good habits, especially when we write
  // functions that will be used more than once and freeing the
  // memory becomes a real necessity
  delete c1;
  delete tex;
  delete leg;
  delete fun;
  delete hdummy;
  delete tge;
  // did i miss any?

}
