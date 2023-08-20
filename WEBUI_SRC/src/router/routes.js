const routes = [
  {
    path: "/",
    component: () => import("layouts/MainLayout.vue"),
    children: [
      { path: "", component: () => import("pages/Home.vue") },
      { path: "home", component: () => import("pages/Home.vue") },
      { path: "page2", component: () => import("pages/IndexPage2.vue") },
      { path: "ifsettings", component: () => import("pages/InterfacesSettings.vue") },
      { path: "services", component: () => import("pages/ServicesPage.vue") },
      { path: "system", component: () => import("pages/SystemPage.vue") },
    ],
  },

  // Always leave this as last one,
  // but you can also remove it
  {
    path: "/:catchAll(.*)*",
    component: () => import("pages/ErrorNotFound.vue"),
  },
];

export default routes;
