#ifndef predict_H
#define predict_H
/*
   function:nº∂∑÷÷ß‘§≤‚
*/

class predict{
	  static const int n = 2;
	  int state;
	  int p[1 << n];
   public:
	  predict();
	  bool jump();
	  void upload(int t);

};


#endif