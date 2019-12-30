function callJDBCDriver(FilePath)
%%Initializing JDBC driver
try
    import java.sql.DriverManager;
    javaclasspath(FilePath)                 
    driverClassName = 'com.mysql.jdbc.Driver';  %chage to full path of jar driver
    % if error change to default again 'com.mysql.jdbc.Driver'

    try
        %This works when the class/JAR is on the static Java classpath
        %Note: driver automatically registers with DriverManager
        java.lang.Class.forName(driverClassName);
    catch
        try
            %Try loading from the dynamic Java path
            classLoader = com.mathworks.jmi.ClassLoaderManager.getClassLoaderManager;
            driverClass = classLoader.loadClass(driverClassName);
        catch %#ok<*CTCH>
            try
                %One more attempt, using the system class-loader
                classLoader = java.lang.ClassLoader.getSystemClassLoader;
                %An alternative, using the MATLAB Main Thread's context
                %classLoader =
                %java.lang.Thread.currentThread.getContextClassLoader;
                driverClass = classLoader.loadClass(driverClassName);
            catch
                %One final attempt-load directly, like this:
                driverClass = eval(driverClassName); %#ok<*NASGU>
                %Or like this (if the driver name is known in advance):
                driverClass = com.mysql.jdbc.Driver;
            end
        end
        %Now manually register the driver with the DriverManager
        %Note: silently fails if driver is not in the static classpath
        DriverManager.registerDriver(driverClass.newInstance);
    end
    %continue with database processing
catch
    error(['JDBC driver ' driverClassName ' not found!']);
    %do some failover activity
end
end