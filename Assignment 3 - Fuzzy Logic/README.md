# Fuzzy Logic
## Support System For Project Team Formation

The problem of optimal team formation is domestic to many areas of work organization including education, sport, and business. It is beyond manual implementation to build near optimal teams as soon as the pool of available personnel grows into several tens. The selection process itself is usually well defined for each team we construct the criteria relating to the required properties of the team members. Because these properties can be arbitrarily combined in the personnel, the objective function becomes self-conflicting. This aggravates the team formation and calls for specialized software support.


We use quantities values to describe the employees’ capabilities like technical expertise and also to describe the budget limits needed to format a team.


The problem is to estimate the level of risk involved in a software engineering project. For the sake of simplicity, we will arrive at our conclusion based on two inputs: project funding and technical experience for the team members.


Suppose our inputs are project_funding and team_experience_level. We can get the fuzzy values for these crisp values by using the membership functions of the appropriate sets.


- The sets defined for <b>project_funding</b> are very low (0,0,10,30), low (10,30,40,60), medium (40,60,70,90), high (70,90,100,100).


- The sets defined for <b>team_experience_level</b> are beginner (0,15,30), intermediate (15,30,45), expert (30,60,60).


- The set defined for the <b>risk</b> is low (0,25,50), normal (25,50,75), high (50,100,100).


### The Rules:

Now that we have the fuzzy values and we can use the fuzzy rules to arrive at the final fuzzy value. The rules are as follows:

1. If <b>project_funding</b> is high or <b>team_experience_level</b> is expert then <b>risk</b> is low.
2. If <b>project_funding</b> is medium and <b>team_experience_level</b> is intermediate or <b>team_experience_level</b> is beginner then <b>risk</b> is normal.
3. If <b>project_funding</b> is very low then <b>risk</b> is high.
4. If <b>project_funding</b> is low and <b>team_experience_level</b> is beginner then <b>risk</b> is high.


### Input Example:

```
Variables: 2
Project Fund: 50
Experience Level: 40
```

### Output Example:
```
Predicted Value (Risk) = 37.5
Risk will be Normal
```