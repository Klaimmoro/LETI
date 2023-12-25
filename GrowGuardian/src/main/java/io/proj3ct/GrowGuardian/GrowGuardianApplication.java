package io.proj3ct.GrowGuardian;
import com.github.siwenyan.common.Sys;
import org.apache.ibatis.jdbc.SQL;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
@SpringBootApplication
public class GrowGuardianApplication {

	public static void main(String[] args) throws SQLException, ClassNotFoundException {

		SpringApplication.run(GrowGuardianApplication.class, args);

	}

}
