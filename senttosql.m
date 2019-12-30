JDBC_Path = 'C:\Users\User\Desktop\mysql-connector-java-5.1.48\mysql-connector-java-5.1.48.jar';
callJDBCDriver(JDBC_Path);

DBName = 'test';
DBUser = 'root';
DBPass = '';
DBPort = 3306;      % See on xampp sql port
conn = database(DBName,DBUser,DBPass,...
                'Vendor','MYSQL','Server','localhost',...
                'AuthType','Server','PortNumber',DBPort);
slCharacterEncoding('UTF-8');
sqlquery = ['INSERT INTO matlabtest (status, j1, j2, j3)',...
            ' VALUES (1, 50, 90, 70)'];
curs = exec(conn,sqlquery);