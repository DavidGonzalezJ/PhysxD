 
#ifndef VerticeNormal_H_
#define VerticeNormal_H_
 
class VerticeNormal {
	private:
		int iv, in;
    public:
		VerticeNormal(int iv, int in)
		{
			this->iv = iv;
			this->in = in;
		}
		VerticeNormal() {};
		~VerticeNormal() {};
		inline int getIV() {
			return iv;
		}
		inline int getIN() {
			return in;
		}
};
#endif
