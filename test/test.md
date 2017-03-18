# Description of test.mini

## Overview
test.mini�� ASCII ���ڿ��� �Է¹��� ��, ���� ������ �������� ���� ����(insertion sort)�� �����Ͽ� �� ����� ������ִ� ���α׷��̴�.
Mini language�� �ִ� 14���� opcode�� ��� ����ϰ� �־� �� opcode�� ���������� �����ϴ��� Ȯ���� �� �ִ�.
**test.mini�� ���� �����Ѵ� �Ͽ� opcode�� fully implemented�Ǿ��ٰ� �� �� ����.**

## Pseudocode in C

* INPUT/OUTPUT
  * INPUT: String S
  * OUTPUT: Sorted in ascending order by ASCII character code(string S)

```c

int main(void)
{
	string S;

	printf("String: ");
	gets(S); // **heap memory overflow�� ����Ǿ� �ִ� gets**

	int n, i, j;
	
	for (n = 0; S[n]; ++n); // n = strlen(S);

	for (i = 1; i < n; ++i)
	{
		key = S[i];
		j = i;
		while (true)
		{
			--j;
			if (j < 0) break;
			if (key >= S[j]) break;
			S[j+1] = S[j];
		}
		S[j+1] = key;
	}
	
	printf("Output: %s\n", S);	
	return 0;
}

```
