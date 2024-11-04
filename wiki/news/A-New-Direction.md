# A New Direction: Short Term and Long Term Goals

November 3, 2024 - [KevDoy](https://github.com/kevdoy) and [InSaneDarwin (csekel)](https://github.com/csekel)

![Blue Prints of new UI elements](/img/news/2024/news-cover-a-new-direction.jpg)

The PureDarwin project, originally created to bring Apple’s open-source Darwin OS to more people, is heading in a fresh new direction with some clear short-term and long-term goals. These new plans are all about breathing new life into PureDarwin. In the short term, we're focused on getting some solid basics in place with graphical interfaces using MATE Desktop and LightDM, so users can get a functional and accessible experience sooner rather than later. Looking further down the line, the long-term goals—shown in some early wireframes—are about creating a fully featured, polished desktop experience that’s easy to use and visually appealing. Plus, a new versioning system will make it clear how PureDarwin is progressing independently from Apple’s Darwin updates, making it easier for everyone to keep track. This refreshed direction sets PureDarwin up to grow from its roots into a user-centered operating system.

### Update to Versioning Approach
To distinguish PureDarwin’s progression from Darwin’s, a new versioning system has been proposed:

- **Old Format:** PureDarwin Test Build 17.2  
  - Structure: PureDarwin [Type of Build] [Darwin Version]
  
- **New Format:** PureDarwin 0.3.0 Alpha (Darwin 24)  
  - Structure: PureDarwin [PureDarwin Version] [State (Alpha, Beta, Stable)] (Darwin [Darwin Version])

This update allows the team to communicate PureDarwin’s independent progress while providing users clarity on release maturity. This approach avoids confusion with outdated versions, like the “Xmas release” (based on Darwin 9 from 2007), which some users still request over more recent builds.

---

### Short-Term Goals (S.T.)
#### Main Project Organization
- Identify additional community volunteers that would like to focus on a specific area of the project
- Clean and reorganize PureDarwin Repositories where required. 
- Update Darwinbuild to work with Github and Meta's xcbuild that was forked to PureDarwin to update and allow PureDarwin to build on itself. 

#### Core OS - Kexts and Userland
- Build All Core Kexts that are required to allow PureDarwin to boot. (IONVMeFamily, DarwinACPIPlatform, etc)
- Finish updating CoreFoundation from the Swift 5.10 source code (the last true framework for CoreFoundation)
- Add Swift Core/Foundation to PureDarwin's Base Image. 

#### Design Focus:  
   - PureDarwin’s current focus is expanding support for graphical user interfaces, aiming for **Wayland** compatibility.
   - The short-term goal concepts (attached below) target a familiar setup with **MATE** Desktop and **LightDM** for login management.
  - The initial experience will be similar to a vanilla **MATE** installation, prioritizing usability and functionality to reach as many users as possible. This target allows the team to focus on foundational tasks needed to achieve a functional graphical environment.

<a href="/img/news/2024/a-new-direction/Figure-1.jpg" target="_blank">
    <img src="/img/news/2024/a-new-direction/Figure-1_thumb.jpg" width="300" class="border mb-1" alt>
</a>
<a href="/img/news/2024/a-new-direction/Figure-2.jpg" target="_blank">
    <img src="/img/news/2024/a-new-direction/Figure-2_thumb.jpg" width="300" class="border mb-1" alt>
</a>


---

### Long-Term Goals (L.T.)

#### Core OS
  - Build a proper installer that will integrate with Darwinbuild for continuous CI build and test process. 
  - More to add from Community!

#### Design Focus -  Our Own Vision for UI Elements 
  - The long-term wireframes and mockups (attached below) illustrate a “blue sky” vision of a fully realized PureDarwin desktop environment.
  - These designs outline the **UI elements** intended for a cohesive user experience, though specifics are not finalized.
  - The wireframes reflect the aspirations for PureDarwin, showcasing what the user interface might eventually look like when developed. However, these are conceptually ambitious, not yet in development.

**Note:** The current focus remains on short-term objectives. While the wireframes serve as a guide for PureDarwin’s future, queries regarding these long-term goals or their completion timeline are discouraged at this stage.

<a href="/img/news/2024/a-new-direction/Figure-3.jpg" target="_blank">
    <img src="/img/news/2024/a-new-direction/Figure-3_thumb.jpg" width="300" class="border mb-1" alt>
</a>
<a href="/img/news/2024/a-new-direction/Figure-4.jpg" target="_blank">
    <img src="/img/news/2024/a-new-direction/Figure-4_thumb.jpg" width="300" class="border mb-1" alt>
</a>
<br>
<a href="/img/news/2024/a-new-direction/Figure-5.jpg" target="_blank">
    <img src="/img/news/2024/a-new-direction/Figure-5_thumb.jpg" width="300" class="border mb-1" alt>
</a>
<a href="/img/news/2024/a-new-direction/Figure-6.jpg" target="_blank">
    <img src="/img/news/2024/a-new-direction/Figure-6_thumb.jpg" width="300" class="border mb-1" alt>
</a>

### Conclusion

With these new targets, the PureDarwin project is heading in an exciting direction, finally giving us the foundation to start building a roadmap for the future. These short-term goals and big-picture aspirations give us something solid to aim for and help shape where we’re going next. While it’s not perfect yet, we’re laying the groundwork and setting a clear direction that’s flexible enough to evolve as we go. The updated versioning system also makes it easier for everyone to follow along with PureDarwin’s progress. Altogether, this new focus brings a sense of purpose to the project and sets us up for a promising future.