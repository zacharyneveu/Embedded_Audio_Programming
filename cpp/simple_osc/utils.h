double amp2db(double amp)
{
    return 20.0*log10(amp);
}

double db2amp(double db)
{
    return pow(10.0, db/20);
}
/*
 * Taken from 
 * https://stackoverflow.com/questions/19944111/creating-a-gaussian-random-generator-with-a-mean-and-standard-deviation
 */
double noise(double db=0)
{//Box muller method
    double stddev = db2amp(db);
    double mean = 0;
    static double n2 = 0.0;
    static int n2_cached = 0;
    if (!n2_cached)
    {
        double x, y, r;
        do
        {
            x = 2.0*rand()/RAND_MAX - 1;
            y = 2.0*rand()/RAND_MAX - 1;

            r = x*x + y*y;
        }
        while (r == 0.0 || r > 1.0);
        {
            double d = sqrt(-2.0*log(r)/r);
            double n1 = x*d;
            n2 = y*d;
            double result = n1*stddev + mean;
            n2_cached = 1;
            return result;
        }
    }
    else
    {
        n2_cached = 0;
        return n2*stddev + mean;
    }
}