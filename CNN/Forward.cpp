#include "Forward.h"
#include "../utils/MatrixFunctions.h"
#include "../common.h"

void convolution(vector<vector<vector<double>>> &result, vector<vector<vector<double>>> image, vector<vector<vector<vector<double>>>> filter, vector<vector<double>> bias, int stride)
{
  int filt1 = filter.size();
  int filt2 = filter[0].size();
  int filt3 = filter[0][0].size();
  int img1 = image.size();
  int img2 = image[0].size();
  int img3 = image[0][0].size();
  int out_dim = (int)((img2 - filt3) / stride) + 1;
  // cout << out_dim << endl;
  if (img1 != filt2)
  {
    cout << "ERROR: Dimensions of Filter and Image must match!" << endl;
  }
  vector<vector<vector<double>>> res(filt1, vector<vector<double>>(out_dim, vector<double>(out_dim, 0)));
  for (int curr_f = 0; curr_f < filt1; curr_f++)
  {
    int curr_y = 0;
    int out_y = 0;
    while (curr_y + filt3 <= img2)
    {
      int curr_x = 0;
      int out_x = 0;
      while (curr_x + filt3 <= img2)
      {
        vector<vector<double>> imageSection;
        for (int i = curr_y; i < curr_y + filt3; i++)
        {
          vector<double> temp;
          for (int j = curr_x; j < curr_x + filt3; j++)
          {
            temp.push_back(image[0][i][j]);
          }
          imageSection.push_back(temp);
        }
        vector<vector<double>> res2;
        multMatrices(res2, filter[curr_f][0], imageSection);
        sum(res2, res2, 0);
        res2[0][0] += bias[curr_f][0];
        res[curr_f][out_y][out_x] = res2[0][0];

        curr_x += stride;
        out_x++;
      }
      curr_y += stride;
      out_y++;
    }
  }
  result = res;
}