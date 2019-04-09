if (node->pos.x >= (PIIF.x + PSDP.x) / 2) // True = Derecho
	{
		if (node->pos.y >= (PIIF.y + PSDP.y) / 2) // True = Superior
		{	
			if (node->pos.z >= (PIIF.z + PSDP.z) / 2) // True = Frontal
			{
				//Cubo Superior Derecho Frontal
				if (SDF == NULL)
				{
					double p = ancho / 2;
					SDF = new Octree(
						Point(PIIF.x + p,     PIIF.y + p,     PIIF.z),
						Point(PIIF.x + 2 * p, PIIF.y + 2 * p, PIIF.z - p),
						ancho / 2
					);
					cout << "Se creo un Cubo Superior Derecho Frontal" << endl;
					cout << "limites :" << endl;
					printPoint(SDF->PIIF);
					printPoint(SDF->PSDP);
				}
				SDF->insert(node);
			}
			else // Posterior
			{
				//Cubo Superior Derecho Posterior
				if (SDP == NULL)
				{
					double p = ancho / 2;
					SDP = new Octree(
						Point((PSDP.x + PIIF.x) / 2, (PSDP.y + PIIF.y) / 2, (PSDP.z + PIIF.z) / 2),
						Point( PSDP.x,                PSDP.y,                PSDP.z),
						ancho / 2
					);
					cout << "Se creo un Cubo Superior Derecho Posterior" << endl;
					cout << "limites :" << endl;
					printPoint(SDP->PIIF);
					printPoint(SDP->PSDP);
				}
				SDP->insert(node);
			}
		}
		else // Inferior
		{
			if (node->pos.z >= (PIIF.z + PSDP.z) / 2) // True = Frontal
			{
				//Cubo Inferior Derecho Frontal
				if (IDF== NULL)
				{
					double p = ancho / 2;
					IDF = new Octree(
						Point(PIIF.x + p,     PIIF.y,     PIIF.z),
						Point(PIIF.x + 2 * p, PIIF.y + p, PIIF.z - p),
						ancho / 2
					);
					cout << "Se creo un Cubo Inferior Derecho Frontal" << endl;
					cout << "limites :" << endl;
					printPoint(IDF->PIIF);
					printPoint(IDF->PSDP);
				}
				IDF->insert(node);
			}
			else // Posterior
			{
				//Cubo Inferior Derecho Posterior
				if (IDP== NULL)
				{
					double p = ancho / 2;
					IDP = new Octree(
						Point(PIIF.x + p,     PIIF.y,     PIIF.z - p),
						Point(PIIF.x + 2 * p, PIIF.y + p, PIIF.z - 2 * p),
						ancho / 2
					);
					cout << "Se creo un Cubo Inferior Derecho Posterior" << endl;
					cout << "limites :" << endl;
					printPoint(IDP->PIIF);
					printPoint(IDP->PSDP);
				}
				IDP->insert(node);
			}
		}
	}
	else // Izquierdo
	{
		if (node->pos.y >= (PIIF.y + PSDP.y) / 2) // True = Superior
		{
			if (node->pos.z >= (PIIF.z + PSDP.z) / 2) // True = Frontal
			{
				//Cubo Superior Izquierdo Frontal
				if (SIF== NULL)
				{
					double p = ancho / 2;
					SIF = new Octree(
						Point(PIIF.x,     PIIF.y + p,     PIIF.z),
						Point(PIIF.x + p, PIIF.y + 2 * p, PIIF.z - p),
						ancho / 2
					);
					cout << "Se creo un Cubo Superior Izquierdo Frontalr" << endl;
					cout << "limites :" << endl;
					printPoint(SIF->PIIF);
					printPoint(SIF->PSDP);
				}
				SIF->insert(node);
			}
			else // Posterior
			{
				//Cubo Superior Izquierdo Posterior
				if (SIP== NULL)
				{
					double p = ancho / 2;
					SIP = new Octree(
						Point(PIIF.x,     PIIF.y + p,     PIIF.z - p),
						Point(PIIF.x + p, PIIF.y + 2 * p, PIIF.z - 2 * p),
						ancho / 2
					);
					cout << "Se creo un Cubo Superior Izquierdo Posterior" << endl;
					cout << "limites :" << endl;
					printPoint(SIP->PIIF);
					printPoint(SIP->PSDP);
				}
				SIP->insert(node);
			}
		}
		else // Inferior
		{
			if (node->pos.z >= (PIIF.z + PSDP.z) / 2) // True = Frontal
			{
				//Cubo Inferior Izquierdo Frontal
				if (IIF== NULL)
				{
					double p = ancho / 2;
					IIF = new Octree(
						Point( PIIF.x,                PIIF.y,                PIIF.z),
						Point((PSDP.x + PIIF.x) / 2, (PSDP.y + PIIF.y) / 2, (PSDP.z + PIIF.z) / 2),
						ancho / 2
					);
					cout << "Se creo un Cubo Inferior Izquierdo Frontal" << endl;
					cout << "limites :" << endl;
					printPoint(IIF->PIIF);
					printPoint(IIF->PSDP);
				}
				IIF->insert(node);
			}
			else // Posterior
			{
				//Cubo Inferior Izquierdo Posterior
				if (IIP== NULL)
				{
					double p = ancho / 2;
					IIP = new Octree(
						Point(PIIF.x,     PIIF.y,     PIIF.z - p),
						Point(PIIF.x + p, PIIF.y + p, PIIF.z - 2 * p),
						ancho / 2
					);
					cout << "Se creo un Cubo Inferior Izquierdo Posterior" << endl;
					cout << "limites :" << endl;
					printPoint(IIP->PIIF);
					printPoint(IIP->PSDP);
				}
				IIP->insert(node);
			}
		}
	}