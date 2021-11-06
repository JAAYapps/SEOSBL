#include "..\memory.h"
#include "..\Graphics.h"
#include "..\text.h"

//int main()
//int main(int argc)
// int main(int argc, char* argv[])
// {
// 	int* m;
// 	memcpy(&m, (int*)&argc, 4);
// 	SetGraphicsColor(ORANGE);
// 	COLOR GraphicsColor = *(COLOR*)GetGraphicsColor();
// 	CreateBufferFilledBox(5, 5, 50, 50);
// 	if(m == (int*)3456)
// 	{
// 		if(GraphicsColor.Alpha == 0xff)
// 		{
//         return 349587;
// 		} else {
// 			return 6666;
// 		}
// 	} else {
//         return 7777;
// 	}
// }

void main(BLOCKINFO* bi)
{
    CopyMemoryBlock(*bi);
    //GetBlockInfo()->BaseAddress = (bi->BaseAddress); // This fixes the GOP address
	InitGraphicsForBlockInfo(GetBlockInfo());

    ClearBufferScreen(0x00004584);

	SetCursorPosition(20, 10);

    // TODO : Paging
	SetFontSize(10);
	SetFontSpacing(4);
	SetCursorPosition(16, 20);

    UINT8 st4[] = "End Program";
	SetGraphicsColor(GREEN);
    printf(st4);

    while(1){__asm__ ("hlt");}
}

#include "..\memory.c"
#include "..\Graphics.c"
#include "..\text.c"