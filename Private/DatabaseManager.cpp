#include "DatabaseManager.h"
#include "SQLiteDatabase.h"
#include "Hash/Blake3.h"
#include "SHA256Hash.h"

// Sets default values
ADatabaseManager::ADatabaseManager()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = false;


}




// Called when the game starts or when spawned
void ADatabaseManager::BeginPlay()
{
	Super::BeginPlay();
}




// Called every frame
void ADatabaseManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Function to create a new user from details passed in. Auto creates userID which auto-increments for every new user
FString ADatabaseManager::CreateUser(FString username, FString password, FString confirmedPass)
{
	FString result = TEXT("null");
	if ((password.Len() >= 8) && (confirmedPass == password) && (username.Len() > 0))
	{

		// Create an instance of FSHA256Hash
    	FSHA256Hash HashGenerator;
		// Convert the string to hash
		HashGenerator.FromString(password);

		// Get the hashed string
		FString HashedPass = HashGenerator.GetHash();

		// Convert the string to hash
		HashGenerator.FromString(username);

		// Get the hashed string
		FString HashedUsername = HashGenerator.GetHash();

		
		// Defines the "DBFilePath" as the directory path to the database and defines "CreateUserSQL" as the SQL query to be run.
		const FString DBFilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() + "Database/UsersDB.db");
		const FString CreateUserSQL = FString::Printf(TEXT("INSERT INTO Users (Username, Password) VALUES('%s', '%s');"), *HashedUsername, *HashedPass);


		//  If the Database opens correctly into "UserDB" so that it can be read and written to, then the following code is run.
		if (FSQLiteDatabase* UserDB = new FSQLiteDatabase();
			UserDB->Open(*DBFilePath, ESQLiteDatabaseOpenMode::ReadWrite))
		{

			// If the "SQLQueryStatement" is created correctly then it runs the following code
			if (FSQLitePreparedStatement* SQLQueryStatement = new FSQLitePreparedStatement();
				SQLQueryStatement->Create(*UserDB, *CreateUserSQL, ESQLitePreparedStatementFlags::Persistent))
			{

				// Runs the SQL query and returns if it ran correctly or not
				bool success = SQLQueryStatement->Execute();


				// If the sql query ran correctly then sends the success message to the console. If it didn't run correctly then it would display the error message.
				if (success)
				{
					UE_LOG(LogTemp, Log, TEXT("User created executed successfully!"));
					result = TEXT("Success");
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to create user: %s"), *UserDB->GetLastError());
					
					if (FString(UserDB->GetLastError()) == FString(TEXT("UNIQUE constraint failed: Users.Username")))
					{
						result = TEXT("Username Taken");
					}
					
					else
					{
						result = TEXT("Fail: Reason Unknown");
					}
				}


				// Removes the SQL query statement from memory so as not to create a memory leak
				SQLQueryStatement->Destroy();
				delete SQLQueryStatement;
			}
			// Removes the database from memory so as not to create a memory leak.
			UserDB->Close();
			delete UserDB;
		}
	}
	else if(password.Len() < 8)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create user: Password too short"));
		result = TEXT("Password is too short");
		
	}
	else if (password != confirmedPass)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create user: Passwords don't match"));
		result = TEXT("Passwords don't match");
	}
	else if (username.Len() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create user: Username is null"));
		result = TEXT("Username can't be blank");
	}

	return result;
}




// Function to login users from details passed in. Checks to see if anyone in database matches entered details
FString ADatabaseManager::Login(FString username, FString password)
{

	// Create an instance of FSHA256Hash
    FSHA256Hash HashGenerator;
	// Convert the string to hash
	HashGenerator.FromString(password);

	// Get the hashed string
	FString HashedPass = HashGenerator.GetHash();

	// Convert the string to hash
	HashGenerator.FromString(username);

	// Get the hashed string
	FString HashedUsername = HashGenerator.GetHash();
	

	// Defines the "DBFilePath" as the directory path to the database and defines "CreateUserSQL" as the SQL query to be run.
	const FString DBFilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() + "Database/UsersDB.db");


	const FString LoginSQL = FString::Printf(TEXT("SELECT Username, Password FROM Users WHERE Username = '%s'  AND Password = '%s';"), *HashedUsername, *HashedPass);
	FString result = TEXT("null");

	//  If the Database opens correctly into "UserDB" so that it can be read and written to, then the following code is run.
	if (FSQLiteDatabase* UserDB = new FSQLiteDatabase();
		UserDB->Open(*DBFilePath, ESQLiteDatabaseOpenMode::ReadWrite))
	{

		// If the "SQLQueryStatement" is created correctly then it runs the following code
		if (FSQLitePreparedStatement* SQLQueryStatement = new FSQLitePreparedStatement();
			SQLQueryStatement->Create(*UserDB, *LoginSQL, ESQLitePreparedStatementFlags::Persistent))
		{

			// Runs the SQL query and returns if it ran correctly or not
			 ESQLitePreparedStatementStepResult stepResult = SQLQueryStatement->Step();


			// If the sql query ran correctly then sends the success message to the console. If it didn't run correctly then it would display the error message.
			 if (stepResult == ESQLitePreparedStatementStepResult::Row)
			 {
				 UE_LOG(LogTemp, Log, TEXT("%s logged in successfully!"), *username);
				 result = TEXT("Success");
			 }
			 else
			 {
				 UE_LOG(LogTemp, Error, TEXT("Failed to login %s : %s"), *username, *UserDB->GetLastError());
				 result = TEXT("Incorrect Username or Password");
			 }


			// Removes the SQL query statement from memory so as not to create a memory leak
			SQLQueryStatement->Destroy();
			delete SQLQueryStatement;
		}
		// Removes the database from memory so as not to create a memory leak.
		UserDB->Close();
		delete UserDB;
	}
	return result;
}
