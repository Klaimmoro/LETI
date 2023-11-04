package io.proj3ct.GrowGuardian.service;


import lombok.Data;
import org.springframework.beans.factory.annotation.Value;

import java.util.Date;

@Data
public class chosenActivity {

    @Value("")
    String Activity = "";

    @Value("")
    int Budget = 0;

    @Value("")
    int peopleCount = 0;

    @Value("")
    int ageCategory = 0;

    @Value("")
    String day = "";

    @Value("")
    String month = "";

    @Value("")
    String time = "";

    @Value("")
    int year = 0;

}
