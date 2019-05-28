void MakeFakeData()
{

  // set the random seed to 0, which means seed will be generated randomly
  // that means we'll get different results each time we run this
  // if we want the same result, we can set the seed to any other value
  gRandom->SetSeed(0);

  // make a text file to be written to
  ofstream fout("data.txt");

  // make a for loop to generate the fake data
  for ( int i = 0; i < 10; ++i )
    {
      // generate an x-coordinate
      double x = (i+1)/10.0;
      // generate a y-coordinate
      double y = i + 3;
      double errsize = y/10.0;
      double err = gRandom->Gaus(0,errsize);
      y += err;
      fout << x << " " << y << " " << errsize << endl;
    }

}
