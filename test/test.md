# Description of test.mini

## Overview
test.mini는 ASCII 문자열을 입력받은 후, 문자 단위로 오름차순 삽입 정렬(insertion sort)을 진행하여 그 결과를 출력해주는 프로그램이다.
Mini language에 있는 14개의 opcode를 모두 사용하고 있어 각 opcode가 정상적으로 동작하는지 확인할 수 있다.
**test.mini가 정상 동작한다 하여 opcode가 fully implemented되었다고 볼 수 없다.**

## Pseudocode in C

* INPUT/OUTPUT
  * INPUT: String S
  * OUTPUT: Sorted in ascending order by ASCII character code(string S)

```c

int main(void)
{
	string S;

	printf("String: ");
	gets(S); // **heap memory overflow를 고려되어 있는 gets**

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
