#define ASSERT(test, a, b) if(a != b) { cout << "Failed test: " << test << endl; cout << a << "\ndoes not match\n" << b << endl;; return 1; };
