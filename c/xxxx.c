
struct MyStruct {
	int p1;
	int p2;
};

int main()
{
	struct MyStruct m_arr[10]; 
	struct MyStruct *m1; 
	int  x; 
	int  y; 
	m1 = &m_arr[3];
	x = m1 - m_arr;
	y = (void*)m1 - (void*)m_arr;

	return 0;	
}
