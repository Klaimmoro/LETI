///*YCbCr по отдельности каждый канал*/
	//sf::Uint8* Y = new sf::Uint8[Image1.getSize().x * Image1.getSize().y * 4];
	//sf::Uint8* Cb = new sf::Uint8[Image1.getSize().x * Image1.getSize().y * 4];
	//sf::Uint8* Cr = new sf::Uint8[Image1.getSize().x * Image1.getSize().y * 4];
	//for (int i = 0; i < Image1.getSize().x * Image1.getSize().y * 4; i += 4) {
	//	Y[i] = 0.299 * pixels[i] + 0.5870 * pixels[i + 1] + 0.114 * pixels[i + 2];
	//	Y[i + 1] = Y[i];
	//	Y[i + 2] = Y[i];

	//	Cb[i] = 0;
	//	Cb[i + 1] = Y[i];
	//	Cb[i + 2] = 128 - (0.168736 * pixels[i]) - (0.331264 * pixels[i + 1]) + (0.5 * pixels[i + 2]);  //0.564 * (pixels[i + 2] - Y[i]); 

	//	Cr[i] = 128 + (0.5 * pixels[i]) - (0.418688 * pixels[i + 1]) - (0.081312 * pixels[i + 2]);  // 0.713 * (pixels[i] - Y[i]); 
	//	Cr[i + 1] = Y[i];
	//	Cr[i + 2] = 0;
	//}




	///*YCbCr сразу*/
	//sf::Uint8* YCbCr = new sf::Uint8[Image1.getSize().x * Image1.getSize().y * 4];
	////YCBCRtoRGB(Y, Cb, Cr, YCbCr, SizeIm);
	//subsampling(Cb, Cr, Y, YCbCr, SizeIm);
	//sf::Uint8* Ydct = new sf::Uint8[Image1.getSize().x * Image1.getSize().y * 4];
	//dct(Ydct,Y, Image1.getSize().x, Image1.getSize().y,window);
	//for (int i = 0; i < Image1.getSize().x * Image1.getSize().y * 4; i += 4) {
	//	Y[i] *= Ydct[i];
	//	Y[i+1] *= Ydct[i+1];
	//	Y[i+2] *= Ydct[i+2];
	//	Y[i] *= Ydct[i];
	//}

	//YCBCRtoRGB(Y, Cb, Cr, YCbCr, SizeIm);

	//sf::Texture YCbCrtext; YCbCrtext.create(Image1.getSize().x, Image1.getSize().y); YCbCrtext.update(YCbCr);
	//sf::Sprite YCbCrSprite; YCbCrSprite.setTexture(YCbCrtext);

	//sf::Texture Ytext; Ytext.create(Image1.getSize().x, Image1.getSize().y); Ytext.update(Y);
	//sf::Sprite YSprite; YSprite.setTexture(Ytext);

	//sf::Texture Cbtext; Cbtext.create(Image1.getSize().x, Image1.getSize().y); Cbtext.update(Cb);
	//sf::Sprite CbSprite; CbSprite.setTexture(Cbtext);

	//sf::Texture Crtext; Crtext.create(Image1.getSize().x, Image1.getSize().y); Crtext.update(Cr);
	//sf::Sprite CrSprite; CrSprite.setTexture(Crtext);

	///*Вывести исходная + Y Cb Cr + YCbCr*/

	///*window.draw(Sprite1);


	//YSprite.setPosition(0, 280);
	//window.draw(YSprite);

	//CbSprite.setPosition(310, 280);
	//window.draw(CbSprite);

	//CrSprite.setPosition(620, 280);
	//window.draw(CrSprite);
	//*/
	//YCbCrSprite.setPosition(0, 600);
	//window.draw(YCbCrSprite);

	//window.display();


	//while (window.isOpen())
	//{

	//	sf::Event event;
	//	while (window.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::Closed)
	//			window.close();
	//	}

	//}

	/*int x = 0; int y = 8; int x1 = x; int y1 = y;
	while (window.isOpen())
	{

	x += 8; x1 = x;
	if (x < Image1.getSize().x) {
	Sprite1.setPosition(x, y);
	Sprite1.setTextureRect(sf::IntRect(x, y, 8, 8));
	}
	else {
	if (y + 8 < Image1.getSize().y) {
	y += 8;
	x = 0;
	continue;
	}
	else {
	x = 1808;
	y = 10000;
	break;
	}
	}


	sf::Event event;
	while (window.pollEvent(event))
	{
	if (event.type == sf::Event::Closed)
	window.close();
	}

	window.draw(Sprite1);
	window.display();


	}*/