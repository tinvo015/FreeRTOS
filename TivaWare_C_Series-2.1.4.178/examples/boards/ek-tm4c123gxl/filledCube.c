

void LCD_DrawCube(unsigned short startX, unsigned short startY, unsigned short sideLen, unsigned short Color)
{
	LCD_DrawRect(startX, startY, sideLen, sideLen, Color);

	LCD_DrawLine(startX, startY, (unsigned short)(startX + (sideLen / sqrt(2))), (unsigned short)(startY - (sideLen / sqrt(2))), Color);

	LCD_DrawLine((unsigned short)(startX + (sideLen / sqrt(2))), (unsigned short)(startY - (sideLen / sqrt(2))),
							 (unsigned short)((startX + (sideLen / sqrt(2))) + sideLen), (unsigned short)(startY - (sideLen / sqrt(2))), Color);

	LCD_DrawLine((unsigned short)((startX + (sideLen / sqrt(2))) + sideLen), (unsigned short)(startY - (sideLen / sqrt(2))),
							 (unsigned short)(startX + sideLen), startY, Color);

	LCD_DrawLine((unsigned short)((startX + (sideLen / sqrt(2))) + sideLen), (unsigned short)(startY - (sideLen / sqrt(2))),
							 (unsigned short)((startX + (sideLen / sqrt(2))) + sideLen), (unsigned short)(startY - (sideLen / sqrt(2)) + sideLen), Color);

	LCD_DrawLine((unsigned short)((startX + (sideLen / sqrt(2))) + sideLen), (unsigned short)(startY - (sideLen / sqrt(2)) + sideLen),
							 (unsigned short)(startX + sideLen), (unsigned short)(startY + sideLen), Color);


	
	LCD_DrawFilledRect(startX, startY, sideLen, sideLen, Color);
        
	for (int i = startX + 1; i < startX + sideLen; i++) {
		LCD_DrawLine((unsigned short) i, (unsigned short) startY, (unsigned short) (i + (sideLen / sqrt(2))),
															(unsigned short) (startY - (sideLen / sqrt(2))), Color);
	}
	
	for (int i = startY + 1; i < startY + sideLen; i++) {
		LCD_DrawLine((unsigned short) (startX + sideLen), (unsigned short) i,
									(unsigned short) (startX + (sideLen / sqrt(2)) + sideLen), 
									(unsigned short) (i - (sideLen / sqrt(2))), Color);
	}

}