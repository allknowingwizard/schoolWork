#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>

static std::mt19937 rng;

class Pixel
{
public:
    int r, g, b;

    Pixel() : r(0), g(0), b(0) {}
    Pixel(int r, int g, int b) : r(r), g(g), b(b) {}

    void swap(Pixel* &p)
    {
        // int r = this->r,  g = this->g,    b = this->b;
        // this->r = p.r;    this->g = p.g;  this->b = p.b;
        // p.r = r;          p.g = g;        p.b = b;
    }
};

void swapPixels(Pixel*& p, Pixel*& q) {
    Pixel* z = p;
    p = q;
    q = z;
}

class Image
{
public:
    static const int width = 256;
    static const int height = 128;
    static const int step = 32;
    Pixel pixel[width*height];
    int penalty[width*height];
    std::vector<int>** neighbors;

    Image()
    {
        if (step*step*step != width*height)
        {
            std::cerr << "parameter mismatch" << std::endl;
            exit(EXIT_FAILURE);
        }

        neighbors = new std::vector<int>*[width*height];

        for (int i = 0; i < width*height; i++)
        {
            penalty[i] = -1;
            neighbors[i] = pixelNeighbors(i);
        }

        int i = 0;
        for (int r = 0; r < step; r++)
        for (int g = 0; g < step; g++)
        for (int b = 0; b < step; b++)
        {
            pixel[i].r = r * 255 / (step-1);
            pixel[i].g = g * 255 / (step-1);
            pixel[i].b = b * 255 / (step-1);
            i++;
        }
    }

    ~Image()
    {
        for (int i = 0; i < width*height; i++)
        {
            delete neighbors[i];
        }
        delete [] neighbors;
    }

    std::vector<int>* pixelNeighbors(const int pi)
    {
        // 01: X-shaped structure
        //const int iRad = 7, jRad = 7;
        //auto condition = [](int i, int j) { return abs(i) == abs(j); };
        //
        // 02: boring blobs
        //const int iRad = 7, jRad = 7;
        //auto condition = [](int i, int j) { return true; };
        //
        // 03: cross-shaped
        //const int iRad = 7, jRad = 7;
        //auto condition = [](int i, int j) { return i==0 || j == 0; };
        //
        // 04: stripes
        const int iRad = 1, jRad = 5;
        auto condition = [](int i, int j) { return i==0 || j == 0; };

        std::vector<int>* v = new std::vector<int>;

        int x = pi % width;
        int y = pi / width;

        for (int i = -iRad; i <= iRad; i++)
        for (int j = -jRad; j <= jRad; j++)
        {
            if (!condition(i,j))
                continue;

            int xx = x + i;
            int yy = y + j;

            if (xx < 0 || xx >= width || yy < 0 || yy >= height)
                continue;

            v->push_back(xx + yy*width);
        }

        return v;
    }

    void shuffle()
    {
        for (int i = 0; i < width*height; i++)
        {
            std::uniform_int_distribution<int> dist(i, width*height - 1);
            int j = dist(rng);
            // pixel[i].swap(pixel[j]);
            Pixel* pi = &(pixel[i]);
            Pixel* pj = &(pixel[j]);
            swapPixels(pi, pj);
        }
    }

    void writePPM(const char* filename)
    {
        std::ofstream fd;
        fd.open(filename);
        if (!fd.is_open())
        {
            std::cerr << "failed to open file " << filename
                      << "for writing" << std::endl;
            exit(EXIT_FAILURE);
        }
        fd << "P3\n" << width << " " << height << "\n255\n";
        for (int i = 0; i < width*height; i++)
        {
            fd << pixel[i].r << " " << pixel[i].g << " " << pixel[i].b << "\n";
        }
        fd.close();
    }

    void updatePixelNeighborhoodPenalty(const int pi)
    {
        for (auto j : *neighbors[pi])
            updatePixelPenalty(j);
    }

    void updatePixelPenalty(const int pi)
    {
        auto pow2 = [](int x) { return x*x; };
        int pen = 0;
        Pixel* p1 = &pixel[pi];
        for (auto j : *neighbors[pi])
        {
            Pixel* p2 = &pixel[j];
            pen += pow2(p1->r - p2->r) + pow2(p1->g - p2->g) + pow2(p1->b - p2->b);
        }
        penalty[pi] = pen / neighbors[pi]->size();
    }

    int getPixelPenalty(const int pi)
    {
        if (penalty[pi] == (-1))
        {
            updatePixelPenalty(pi);
        }
        return penalty[pi];
    }

    int getPixelNeighborhoodPenalty(const int pi)
    {
        int sum = 0;
        for (auto j : *neighbors[pi])
        {
            sum += getPixelPenalty(j);
        }
        return sum;
    }

    void iterate()
    {
        std::uniform_int_distribution<int> dist(0, width*height - 1);       

        int i = dist(rng);
        int j = dist(rng);

        int sumBefore = getPixelNeighborhoodPenalty(i)
                        + getPixelNeighborhoodPenalty(j);

        int oldPenalty[width*height];
        std::copy(std::begin(penalty), std::end(penalty), std::begin(oldPenalty));

        //pixel[i].swap(pixel[j]);
        Pixel* pi = &(pixel[i]);
        Pixel* pj = &(pixel[j]);
        swapPixels(pi, pj);
        updatePixelNeighborhoodPenalty(i);
        updatePixelNeighborhoodPenalty(j);

        int sumAfter = getPixelNeighborhoodPenalty(i)
                       + getPixelNeighborhoodPenalty(j);

        if (sumAfter > sumBefore)
        {
            // undo the change
            //pixel[i].swap(pixel[j]);
            Pixel* pi = &(pixel[i]);
            Pixel* pj = &(pixel[j]);
            swapPixels(pi, pj);
            std::copy(std::begin(oldPenalty), std::end(oldPenalty), std::begin(penalty));
        }
    }
};

int main(int argc, char* argv[])
{
    int seed;
    if (argc >= 2)
    {
        seed = atoi(argv[1]);
    }
    else
    {
        std::random_device rd;
        seed = rd();
    }
    std::cout << "seed = " << seed << std::endl;
    rng.seed(seed);

    const int numIters = 1000000;
    const int progressUpdIvl = numIters / 100;
    Image img;
    img.shuffle();
    for (int i = 0; i < numIters; i++)
    {
        img.iterate();
        if (i % progressUpdIvl == 0)
        {
            std::cout << "\r" << 100 * i / numIters << "%";
            std::flush(std::cout);
        }
    }
    std::cout << "\rfinished!" << std::endl;
    img.writePPM("AllColors2.ppm");

    return EXIT_SUCCESS;
}