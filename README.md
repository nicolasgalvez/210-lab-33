# Lab 29 Alpha
This will be the alpha release branch

3. Development: where the actual coding takes place. This phase is often the longest, as it involves not just coding but also unit testing to ensure that individual parts of the software work correctly.

4. Testing: the software is rigorously tested to identify and fix any bugs or issues. Various tests are conducted: system testing, integration testing, and user acceptance testing), to ensure the software meets all requirements and functions as intended.

## Requirements Analysis
Suppose the project's stakeholders have met, and determined the following set of requirements for this software release:

It needs to be a simulation.
The simulation can be anything in life or nature.
The simulation needs to be a discrete-event simulation (time-based).
The simulation must feature an std::map.
The simulation must retrieve data from an external file.
The value in the map's key-value pair must be a 3-element std::array of std::lists. This makes a nested data structure, with the outer map hosting an inner array of three lists.
There must be at least 100 lines of data processed by the program. LLM's are well-known for helping to generate data like this.
The driver program should neatly display the std::map data.
The driver should show the initial state of the environment, and how it changes after a certain number of time periods. Use at least 25 time periods.
The program must have at least one function.
 
## Design Proposal, Pseudocode, & Mockup
Imagine the subject and details of your project, and write a proposal. You can type it into the submission box or submit a document. The proposal should describe the project and explain its implementation. Explain how the simulation will take place, and what it will show. Explain the time periods you've chosen.

The pseudocode will be coded using VS Code connected to a GitHub repository.

Pseudocode is plain-language comments, placed in your code as actual comments, that serve as a coding framework. What are the major steps and blocks of code necessary for the project? What functions? Put placeholders for all those with pseudocode comments.

Write a mockup, which is a bare-bones wireframe of your code. It should have dummy variables and do trivial outputs to demonstrate that the functions work, are passing data, and that the data structure is coded properly with one data element.

# Proposal:

## Project Overview:
My project will simulate a weather sensor for a garden, by allowing input of weather data for a given day, and simulating sensor reading for 3 sensors:

1. Battery charge
2. Soil moisture
3. Temperature

It should be built in a way that will allow more sensors to be added later, for example wind speed or light.


## Implementation:

I plan to refactor the weather monitor project I submitted for a previous lab. 

With the following changes:

Refactor the soil monitor project I submitted for a previous lab. With the following changes:
1. Allow the user to select a date in the past
2. Save real weather data to a file simulating an API call.
3. Use the data to make a dirty (har har) soil temp calculation, and charging speed.
4. Change the polling interval for the fake device to an hour instead of 15 minutes.
5. Add Tests

I will use a `std::map` of `std::array` to store the 3 datapoints, as well as the timestamp.

If time allows, I will create a std::class with methods for polling data from the simulated sensors. Properties are a map above. The constructor will take the map of the data from the file or API and build out the map by simulating an entire day.

### Interface

(Nice to have)

The user interface will allow you to select the day, the watering time, and the amount of water. In the case a file or cached API call is used, there will only be limited days available for selection.

The class will be decoupled from the main function to input by file as well for testing purposes (although I may try to get gtest working if I have time).

## Simulated events:
The program will fetch 5 days from the file/API, and display a table of data in ascending datetime order. If I get around to programming the interface, you can choose the start day for the next 5 days. 5 * 24 will meet the 100 record requirement.

# Pseudocode

See main.cpp

# Wireframe

See main.cpp