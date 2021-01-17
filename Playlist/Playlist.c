#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<stdbool.h>
#include<ctype.h>
#define MAX 120

typedef struct music* Song;
typedef struct music {
	char song[MAX];
	char artist[MAX];
	char hashtags[MAX];
	Song next;
}Music;

Song Alokacija();
void ProcitajDatoteku(Song);
void DodajNovi(Song, char[], char[], char[]);
void DodajuDatoteku(char[], char[], char[]);
void Ispis(Song);
void Izbornik();
bool DodajPjesmu(Song);
void PretragaPoImenu(Song, char[]);
void PretragaPoIzvodacu(Song, char[]);
void PretragaPoHashtagu(Song, char[]);
bool DaLiJeHashtag(char[], char[]);

int main()
{
	Song head;
	head = Alokacija();
	int izbor;
	bool test = false;
	char buffer[MAX], buff[5];
	ProcitajDatoteku(head);

	do
	{
		Izbornik();
		scanf("%d", &izbor);
		switch (izbor)
		{
		case 1:
			test = DodajPjesmu(head);
			if (test)
				printf("Pjesma je uspjesno dodana!\n");
			else
				printf("Nesto je poslo po zlu, pokusajte ponovno!\n");
			break;
		case 2:
			printf("Unesite ime pjesme: ");
			fgets(buff, sizeof(buff), stdin);
			fgets(buffer, MAX, stdin);
			PretragaPoImenu(head, buffer);
			break;
		case 3:
			printf("Unesite ime izvodaca: ");
			fgets(buff, sizeof(buff), stdin);
			fgets(buffer, MAX, stdin);
			PretragaPoIzvodacu(head, buffer);
			break;
		case 4:
			printf("Unesite hashtag: ");
			fgets(buff, sizeof(buff), stdin);
			fgets(buffer, MAX, stdin);
			PretragaPoHashtagu(head, buffer);
			break;
		case 5:
			Ispis(head);
			break;
		default:
			printf("Krivi unos, molimo pokusajte ponovno: \n");
			break;
		}
	} while (izbor);


	return 0;
}

Song Alokacija()
{
	Song novi;
	novi = (Song)malloc(sizeof(Music));
	strcpy(novi->artist, "");
	strcpy(novi->hashtags, "");
	strcpy(novi->song, "");
	novi->next = NULL;
	return novi;
}

void ProcitajDatoteku(Song head)
{
	FILE* fp;
	fp = fopen("playlist1.txt", "r");


	if (fp == NULL)
	{
		printf("Datoteka ne postoji, prilikom dodavanja pjesme stvara se datoteka playlist1.txt!!!!\n\n");
		return;
	}

	char song[MAX] = "";
	char artist[MAX] = "";
	char hashtags[MAX] = "";

	while (!feof(fp))
	{
		fgets(song, MAX, (FILE*)fp);
		fgets(artist, MAX, (FILE*)fp);
		fgets(hashtags, MAX, (FILE*)fp);

		DodajNovi(head, song, artist, hashtags);

		memset(song, 0, sizeof(song));
		memset(artist, 0, sizeof(artist));
		memset(hashtags, 0, sizeof(hashtags));
	}

	fclose(fp);

}

void DodajNovi(Song head, char song[], char artist[], char hashtags[])
{
	Song novi = Alokacija();
	if (!strcmp(song, "") || !strcmp(artist, "") || !strcmp(hashtags, ""))
	{
		return;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		strcpy(novi->artist, artist);
		strcpy(novi->hashtags, hashtags);
		strcpy(novi->song, song);
		head->next = novi;
	}

}

void Ispis(Song temp)
{
	if (temp->next == NULL)
		printf("Lista je prazna!\n");
	else
	{
		temp = temp->next;
		while (temp->next != NULL)
		{
			printf("\nIme pjesme:\t%s\n", temp->song);
			printf("Ime izvodaca:\t%s\n", temp->artist);
			printf("Hashtags:\t%s\n\n", temp->hashtags);
			temp = temp->next;
		}
		printf("\nIme pjesme:\t%s\n", temp->song);
		printf("Ime izvodaca:\t%s\n", temp->artist);
		printf("Hashtags:\t%s\n\n", temp->hashtags);
	}
}

void Izbornik()
{
	printf("----------------------------------------\n");
	printf("<1. Dodavanje pjesme>\n");
	printf("<2. Pretraga po imenu>\n");
	printf("<3. Pretraga po izvodacu>\n");
	printf("<4. Pretraga po hashtagu>\n");
	printf("<5. Ispis zbirke pjesama>\n");
	printf("<0. Izlaz>\n");
	printf("----------------------------------------\n");
}

void DodajuDatoteku(char song[], char artist[], char hashtags[])
{
	FILE* fp;
	fp = fopen("playlist1.txt", "a");

	fputs(song, (FILE*)fp);

	fputs(artist, (FILE*)fp);

	fputs(hashtags, (FILE*)fp);

	fclose(fp);
}

bool DodajPjesmu(Song head)
{
	char song[MAX];
	char artist[MAX];
	char hashtags[MAX];
	char buff[5];

	fgets(buff, 5, stdin);
	printf("Unesite naziv pjesme: ");
	fgets(song, MAX, stdin);
	printf("Unesite ime izvodaca: ");
	fgets(artist, MAX, stdin);
	printf("Unesite hashtagove: ");
	fgets(hashtags, MAX, stdin);

	DodajNovi(head, song, artist, hashtags);
	DodajuDatoteku(song, artist, hashtags);

	return true;
}

void PretragaPoImenu(Song head, char buff[])
{
	int test = 0;
	if (head->next == NULL)
	{
		printf("Lista je prazna...\n");
		test = 2;
	}
	else
	{
		head = head->next;
		while (head->next != NULL)
		{
			if (!strcmp(head->song, buff))
			{
				printf("\nIme izvodaca:\t%s\n", head->artist);
				printf("Hashtags:\t%s\n\n", head->hashtags);
				if (test != 1)
					test = 1;
			}
			head = head->next;
		}
		if (!strcmp(head->song, buff))
		{
			printf("\nIme izvodaca:\t%s\n", head->artist);
			printf("Hashtags:\t%s\n\n", head->hashtags);
			if (test != 1)
				test = 1;
		}
	}
	if (test == 0)
		printf("Takve pjeme nema u Vasoj listi!\n");
}

void PretragaPoIzvodacu(Song head, char buff[])
{
	int test = 0;
	if (head->next == NULL)
	{
		printf("Lista je prazna...\n");
		test = 2;
	}
	else
	{
		head = head->next;
		while (head->next != NULL)
		{
			if (!strcmp(head->artist, buff))
			{
				printf("\nIme pjesme:\t%s\n", head->song);
				printf("Hashtags:\t%s\n\n", head->hashtags);
				if (test != 1)
					test = 1;
			}
			head = head->next;
		}
		if (!strcmp(head->artist, buff))
		{
			printf("\nIme pjesme:\t%s\n", head->song);
			printf("Hashtags:\t%s\n\n", head->hashtags);
			if (test != 1)
				test = 1;
		}
	}
	if (test == 0)
		printf("U listi ne postoji nijedna pjesma toga izvodaca!\n");
}

void PretragaPoHashtagu(Song head, char buff[])
{
	int test = 0;
	if (head->next == NULL)
	{
		printf("Lista je prazna...\n");
		test = 2;
	}
	else
	{
		head = head->next;
		while (head->next != NULL)
		{
			if (DaLiJeHashtag(head->hashtags, buff))
			{
				printf("\nIme pjesme:\t%s\n", head->song);
				printf("Ime izvodaca:\t%s\n\n", head->hashtags);
				if (test != 1)
					test = 1;
			}
			head = head->next;
		}
		if (DaLiJeHashtag(head->hashtags, buff))
		{
			printf("\nIme pjesme:\t%s\n", head->song);
			printf("Ime izvodaca:\t%s\n\n", head->hashtags);
			if (test != 1)
				test = 1;
		}
	}
	if (test == 0)
		printf("U listi ne postoji nijedna pjesma s tim hashtagom!\n");
}

bool DaLiJeHashtag(char hashtags[], char hash[])
{
	char buff[MAX];
	int duljina = strlen(hashtags), i = 1, j = 0;

	if (hash[0] != '#')
	{
		while (hashtags[i] != '\n')
		{
			memset(buff, 0, sizeof(buff));
			while (hashtags[i] != '#' && hashtags[i] != '\n')
			{
				buff[j] = hashtags[i];
				j++;
				i++;
			}
			buff[j] = '\n';
			if (!strcmp(buff, hash))
				return true;
			j = 0;
			i++;
		}
		return false;
	}
	else
	{
		while (hashtags[i] != '\n')
		{
			memset(buff, 0, sizeof(buff));
			buff[0] = '#';
			j = 1;
			while (hashtags[i] != '#' && hashtags[i] != '\n')
			{
				buff[j] = hashtags[i];
				j++;
				i++;
			}
			buff[j] = '\n';
			if (!strcmp(buff, hash))
				return true;
			i++;
		}
		return false;
	}


}