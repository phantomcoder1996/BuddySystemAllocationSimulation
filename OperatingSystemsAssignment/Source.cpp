#include "allocator3.h"

int main()
{

	
	pcb p1,p2,p3,p4,p5,p6,p7,p8,p9,p10;
	MemoryAllocator memo;
	
	p2.p_size = 8;
	memo.allocate(p2);
	cout << " processs 1 alocation" << p2.startAddress << endl;
	p3.p_size = 4;
	memo.allocate(p3);
	cout << " processs 2 alocation" << p3.startAddress << endl;
	p4.p_size = 4;
	memo.allocate(p4);
	cout << " processs 3 alocation" << p4.startAddress << endl;
	p5.p_size = 512;
	memo.allocate(p5);
	cout << " processs 4 alocation" << p5.startAddress << endl;
	p6.p_size = 256;
	memo.allocate(p6);
	cout << " processs 5 alocation" << p6.startAddress << endl;
	p7.p_size = 512;
	memo.allocate(p7);
	cout << " processs 6 alocation" << p7.startAddress << endl;
	p8.p_size = 256;
	memo.allocate(p8);
	cout << " processs 7 alocation" << p8.startAddress << endl;
	p9.p_size = 16;
	memo.allocate(p9);
	cout << " processs 8 alocation" << p9.startAddress << endl;
	p10.p_size = 2;
	memo.allocate(p10);
	cout << " processs 9 alocation" << p10.startAddress << endl;

	p1.p_size = 1;
	memo.allocate(p1);
	cout << " processs 10 alocation" << p1.startAddress << endl;

	memo.deallocate(p2);
	int level = 10 - int(ceil(log2(p2.p_size)));
		cout << "processp1 deallocated at level " << level<<endl;
		cout << "size of level " << level << ":" << memo.buddylist[level].size() << endl << endl;
	memo.deallocate(p3);
	level = 10 - int(ceil(log2(p3.p_size)));
	cout << "processp2 deallocated at level " << level << endl;
	cout << "size of level " << level << ":" << memo.buddylist[level].size() << endl << endl;
	memo.deallocate(p4);
	level = 10 - int(ceil(log2(p4.p_size)));
	cout << "processp3 deallocated at level " << level << endl;
	cout << "size of level " << level << ":" << memo.buddylist[level].size() << endl << endl;
	memo.deallocate(p6);
	level = 10 - int(ceil(log2(p6.p_size)));
	cout << "processp5 deallocated at level " << level << endl;
	cout << "size of level " << level << ":" << memo.buddylist[level].size() << endl << endl;
	memo.deallocate(p9);
	level = 10 - int(ceil(log2(p9.p_size)));
	cout << "processp8 deallocated at level " << level << endl;
	cout << "size of level " << level << ":" << memo.buddylist[level].size() << endl << endl;
	memo.deallocate(p10);
	level = 10 - int(ceil(log2(p10.p_size)));
	cout << "processp9 deallocated at level " << level << endl;
	cout << "size of level " << level << ":" << memo.buddylist[level].size() << endl << endl;
	memo.deallocate(p1);
	level = 10 - int(ceil(log2(p1.p_size)));
	cout << "processp10 deallocated at level " << level << endl;
	cout << "size of level " << level << ":" << memo.buddylist[level].size() << endl << endl;
	memo.deallocate(p5);
	level = 10 - int(ceil(log2(p5.p_size)));
	cout << "processp4 deallocated at level " << level << endl;
	cout << "size of level " << level << ":" << memo.buddylist[level].size() << endl << endl;

	cout << "nodes at levle 0" << memo.buddylist[0].size() << endl;
	for (int i = 1; i < 11; i++)
	{

		if (memo.buddylist[i].size() > 0)
			cout << "error at level " << i << endl;
	}
	return 0;
}